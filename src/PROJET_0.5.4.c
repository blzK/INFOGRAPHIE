/* ===============================================================
  E.Incerti - Université de Marne-la-Vallée - incerti@univ-mlv.fr 
  ============================================================= */

#include <stdio.h>
#include <g3x.h>
#include "const.h"
#include "shape.h"
#include "ressort.c"
#include "sphere.c"
#include "tore.c"
#include "pave.c"
#include "cylindre.c"
  




  typedef struct{
  /*	double c[16];*/
  	double * c;
  } HMat;
  HMat currMat;
  double *ptr_currMat;
  G3Xpoint *ptr_currRep;
  G3Xpoint R0;
/*
Chaque Node a une matrice de transformation
Quand on dessine l'arbre de la scène on devra appliquer pour chaque noeud
la transformation 
*/

typedef struct Node{
	struct Node * nodes;
	struct Shape * shapes;
	int type;/*0 : feuille, 1 : macro-object, 2 : noeud */
	int shapesNo; 
	int sonsNo;/*Nombre de fils*/
  HMat Md, Mi, Mn; /*Matrices 4x4 directe, inverse, normale*/
} Node;





void initNodeMatrix(struct Node * str){
	str->Md.c=malloc(16*sizeof(double));
	str->Mi.c=malloc(16*sizeof(double));
	str->Mn.c=malloc(16*sizeof(double));
	memset(str->Md.c, 0,16*sizeof(double));
	memset(str->Mi.c, 0,16*sizeof(double));
	memset(str->Mn.c, 0,16*sizeof(double));
	g3x_MakeIdentity(str->Md.c);
	g3x_MakeIdentity(str->Mi.c);
	g3x_MakeIdentity(str->Mn.c);
	/*G3Xloadidentity(str->Md.c);*/
	/*str->Md.c=G3Xidentity;*/
	/*int i;

	for (i = 0; i < 16; ++i)
	{
		printf("Matrice directe i = %d -> %f\n", i, str->Md.c[i]);
	}*/

	/*g3x_MPrintHMat(*(str->Md.c));*/

	}

	void initMatrix(HMat * mat){
		mat->c=malloc(16*sizeof(double));

		memset(mat->c, 0,16*sizeof(double));

		g3x_MakeIdentity(mat->c);

	/*g3x_MPrintHMat(str->Md.c);*/

	}
	void initMatrixZero(HMat * mat){
		mat->c=malloc(16*sizeof(double));

		memset(mat->c, 0,16*sizeof(double));

	}

	void InitializeShape(Shape * str){
		glColor4fv(orange);       
		glTranslatef(5.,5.,-1);
		switch (str->ID){
			case 0:
			InitializePave(str);
			break;
			case 1:
			InitializeSphere(str);
			break;
			case 2:
			InitializeCylindre(str);
			break;
			case 3:
			InitializeTore(str);
			break;
			case 4: 
			InitializeRessort(str);
			break;
		}       
	}


	/*FORMES CANONIQUES*/
	Shape pave_canonical;
	Shape cylindre_canonical;
	Shape sphere_canonical;
	Shape tore_canonical;
	Shape ressort_canonical;
	Shape * ptr_pave_canonical= &pave_canonical;
	Shape * ptr_cylindre_canonical=&cylindre_canonical;
	Shape * ptr_sphere_canonical=&sphere_canonical;
	Shape * ptr_tore_canonical=&tore_canonical;
	Shape * ptr_ressort_canonical=&ressort_canonical;

	void InitCanonical(){

	/*FORMES CANONIQUES*/

		pave_canonical.ID=0;
		sphere_canonical.ID=1;
		cylindre_canonical.ID=2;
		tore_canonical.ID=3;
		ressort_canonical.ID=4;

		InitializeShape(&pave_canonical); 
		InitializeShape(&cylindre_canonical);
		InitializeShape(&sphere_canonical);
		InitializeShape(&tore_canonical);
		InitializeShape(&ressort_canonical);


	}



/*Mise à jour des coordonnées de la Shape après application de la matrice
constituée par la multiplication de toutes les matrices précédentes */


/*
Il faut faire la multiplication avec la forme canonique !
donc sauvegarder un type canonique...
*/

bool UpdateShape2(Shape * str,  double *ptr_Mat){

	G3Xpoint *v2=str->vrtx;
	G3Xpoint *vn= str->norm;
	G3Xpoint *vC;
	G3Xpoint *vCn;

	switch(str->ID){
		case 0:
		vC=ptr_pave_canonical->vrtx;
		vCn=ptr_pave_canonical->norm;
		break;    
		case 1: 
		vC=ptr_sphere_canonical->vrtx;
		vCn=ptr_sphere_canonical->norm;
		break; 
		case 2:
		vC=ptr_cylindre_canonical->vrtx;
		vCn=ptr_cylindre_canonical->norm;
		break;
		case 3:
		vC=ptr_tore_canonical->vrtx;  
		vCn=ptr_tore_canonical->norm;
		break;
		case 4: 
		vC=ptr_ressort_canonical->vrtx;
		vCn=ptr_ressort_canonical->norm;
		break;
	} 

	int q;      
	q=0;

	G3Xpoint ResultPoint;
	G3Xpoint ResultPoint2;

	for (q = 0; q < str->pointNo; ++q){
		g3x_ProdHMatPoint(ptr_Mat, *vC, ResultPoint);
		/*Transformation des vertex*/
		(*v2)[0]=ResultPoint[0];
		(*v2)[1]=ResultPoint[1];
		(*v2)[2]=ResultPoint[2];
		v2++; 
		vC++;
	}

	for (q = 0; q < str->normNo; ++q){
		g3x_ProdHMatPoint(ptr_Mat, *vCn, ResultPoint2);
		/*Transformation des normales*/
		(*vn)[0]=ResultPoint2[0];
		(*vn)[1]=ResultPoint2[1];
		(*vn)[2]=ResultPoint2[2];
		vCn++;  
		vn++;    

	}
/*printf("%f  %f  %f\n", *vC[0],vC[1],vC[2]);*/

	return true; 

}  

void DrawShape(Shape * str){

	g3x_Material(str->col,str->ambi,str->diff,str->spec,str->shine,str->alpha);

	printf("drawing shape %d\n", str->ID);
	switch (str->ID){
		case 0: 
		g3x_Material(vert,ambi,diff,spec,shin,1.);
		DrawPave(str);
		break;
		case 1:  
		g3x_Material(rouge,ambi,diff,spec,shin,1.);
		DrawSphere(str);
		break;
		case 2:     
		/*g3x_Material(orange,ambi,diff,spec,shin,1.);*/     
		DrawCylindre(str);
		break;
		case 3:
		g3x_Material(jaune,ambi,diff,spec,shin,1.);
		DrawTore(str);
		break;
		case 4:
		g3x_Material(cyan,ambi,diff,spec,shin,1.);
		DrawRessort(str);   
		break;
	}        
}




void DrawLeaf(Node * str){ 
	int i,size;
	size=(str->shapesNo);
	for(i=0;i<size;i++){
		/*UpdateShape2(&(str->shapes)[i],ptr_currMat);*/
		DrawShape(&(str->shapes)[i]);
	}

}



int level=0;

void DrawNodes(Node * str){
	int size,i;

	size=str->sonsNo;

	/*Si c'est un Objet*/
	if(str->type==0)
	{
		printf("level : %d I'm an object i have %d sons and %d shapes\n",level, size,str->shapesNo );
		DrawLeaf(str);
	}

	/*Si c'est un Macro-Objet*/
	else if(str->type==1)
	{
		printf("level : %d  I'm a SubNode i have %d sons and %d shapes my type is %d\n",level, size,str->shapesNo, str->type );
		printf("Drawing macro-object %d\n",size );


		/*Dessin*/
		DrawLeaf(str);
		/*Dessine ses fils*/
		printf("Go to son \n");
		Node *son;
		for(i=0;i<(str->sonsNo);i++){
			printf("test\n");
			son=&((str->nodes)[i]);
			printf("looking son %d type %d\n", i, son->type );
			level++;
			DrawNodes(son);
			level--;
		}

	}
	/*Si c'est un noeud*/
	else if(str->type==2)
	{
		printf("level : %d  I'm a Node i have %d sons and my type is %d\n",level, size, str->type );
		printf("Go to son \n");
		Node *son;


		for(i=0;i<(str->sonsNo);i++)
		{
			printf("test\n");
			son=&((str->nodes)[i]);
			printf("looking son %d type %d\n", i, son->type );
			level++;
			DrawNodes(son);
			level--;
		}

	}


	/*Application de la matrice inverse*/
	/*g3x_ProdHMat(ptr_Mat,str->Mi.c,ptr_Mat);
	/*g3x_ProdHMat(str->Mi.c, ptr_Mat,ptr_Mat);*/


}



void UpdateLeaf(Node * str, double * ptr_Mat){

	int i,size;
	size=(str->shapesNo);
/*Dessin*/ 
	printf("shapes \n");
	for(i=0;i<size;i++){ 
		UpdateShape2(&(str->shapes)[i],ptr_Mat);
	}

}



/*
Mise à jour des coordonnées après changement des matrices.

Parcours l'arbre, et obtiens les matrices résultantes à chaque feuille.
N0 | sur chacune de ses shapes UpdateShape2(MdN0) 
N1 | UpdateShape2(MdN0 x MdN1)
N2 | UpdateShape2(MdN0 x MdN1 x MdN1)

temp=No;
temp=N0xN1;
*/


void UpdateNode(Node * str, double * ptr_Mat){
	int size,i;
	size=str->sonsNo;

	/*Application de la matrice directe*/
	g3x_ProdHMat(ptr_Mat, str->Md.c, ptr_Mat);
	/*g3x_ProdHMat(str->Md.c, ptr_Mat,  ptr_Mat);*/

/*Affichage de la matrice courante*/
	printf("********level = %d********\n",level );
	int k;

	for (k = 0; k < 16; ++k)
	{
		printf("Matrice directe k = %d -> %f\n", k, ptr_Mat[k]);
	}

	
	if(str->type==0){
		printf("I'm an object %d\n",size );
		UpdateLeaf(str,ptr_Mat);
	}

	else if(str->type==1){
		/*Si c'est un macro-object*/
		printf("I'm a SubNode my size is %d my type is %d\n",size, str->type );
		printf("Drawing macro-object %d\n",size );

	/*Dessin*/
		printf("shapes \n");
		for(i=0;i<str->shapesNo;i++){
			UpdateShape2(&(str->shapes)[i],ptr_Mat);
		}
	/*Dessine ses fils*/
		printf("Go to son \n");
		Node *son;
		for(i=0;i<(str->sonsNo);i++){
			printf("test\n");
			son=&((str->nodes)[i]);
			printf("looking son %d type %d\n", i, son->type );
			UpdateNode(son, ptr_Mat);

		}


	}
	else if(str->type==2){
/*Si c'est un noeud*/
		printf("I'm a Node my size is %d my type is %d\n",size, str->type );
		printf("Go to son \n");
		Node *son;

		for(i=0;i<(str->sonsNo);i++)
		{
			printf("test\n");
			son=&((str->nodes)[i]);
			printf("looking son %d type %d\n", i, son->type );
			UpdateNode(son, ptr_Mat);
		}


	}

	/*Application de la matrice inverse*/
	g3x_ProdHMat(ptr_Mat,str->Mi.c,ptr_Mat);
	/*g3x_ProdHMat(str->Mi.c, ptr_Mat,ptr_Mat);*/

}











Shape * test(Shape * s){
	float r,x,y,z,theta,phi,i,j;
	float t;	
	
	int n=4;
	G3Xpoint *vt=s->vrtx;
	for(i=0;i<N;i++){

		for (j=0;j<P;j++)
		{
			/*t= pow(r,n)*sin(theta*n)*cos(phi*n);*/

			r = sqrt((*vt)[0]*(*vt)[0] + (*vt)[1]*(*vt)[1] +(*vt)[2]*(*vt)[2]);
			theta = atan2(sqrt((*vt)[0]*(*vt)[0] + (*vt)[1]*(*vt)[1] ) , (*vt)[2]);
			phi = atan2((*vt)[1],(*vt)[0]); 
			/*printf("\n %d %d %d %d %d ",t,r ,n, theta,phi);*/
			/*printf("\n %f %f %f !\n",(*vt)[0],(*vt)[1], (*vt)[2]);*/
			(*vt)[0] = pow(r,n) * sin(theta*n) * cos(phi*n);
			(*vt)[1] = pow(r,n) * sin(theta*n) * sin(phi*n);
			(*vt)[2] = pow(r,n) * cos(theta*n);
			/*printf("\n %f %f %f !\n",(*vt)[0],(*vt)[1], (*vt)[2]);*/
			vt++;
		}
	}

	return s;
}


/*Doit aussi transformer les normales !*/

void MakeTransformation(Node * outputNode, double translation[3], double rotation[3], double homothetie[3] ){

	/*Transformation directe*/
	HMat temp;
	HMat temp21;
	HMat temp22;
	HMat temp23;
	HMat temp3;
	initMatrix(&temp);
	initMatrix(&temp21);
	initMatrix(&temp22);
	initMatrix(&temp23);
	initMatrix(&temp3);
	
	if(translation!=NULL){
		g3x_MakeTranslationXYZ(temp.c, translation[0],translation[1],translation[2]);

		/*g3x_ProdHMat(temp.c, outputNode->Md.c,outputNode->Md.c);*/
		g3x_ProdHMat(outputNode->Md.c,temp.c, outputNode->Md.c);
	}

	if(rotation!=NULL){
		if(rotation[0]!=0.){
			g3x_MakeRotationX(temp21.c, rotation[0]);
			/*g3x_ProdHMat(temp21.c,outputNode->Md.c,outputNode->Md.c);*/
			g3x_ProdHMat(outputNode->Md.c, temp21.c,outputNode->Md.c);

		}
		if(rotation[1]!=0.){
			g3x_MakeRotationY(temp22.c,rotation[1]);
			/*g3x_ProdHMat(temp22.c,outputNode->Md.c,outputNode->Md.c);*/
			g3x_ProdHMat(outputNode->Md.c,temp22.c,outputNode->Md.c);
		}
		if(rotation[2]!=0.){
			g3x_MakeRotationZ(temp23.c,rotation[2]);
			/*g3x_ProdHMat(temp23.c,outputNode->Md.c,outputNode->Md.c);*/
			g3x_ProdHMat(outputNode->Md.c,temp23.c,outputNode->Md.c);
		}
	}


	if(homothetie!=NULL){

		g3x_MakeHomothetieXYZ(temp3.c, homothetie[0],homothetie[1],homothetie[2]);
		/*g3x_ProdHMat(temp3.c,outputNode->Md.c,outputNode->Md.c);*/
		g3x_ProdHMat(outputNode->Md.c,temp3.c,outputNode->Md.c);
	}


	/*g3x_MakeRotationX(ptr_n1->Md.c, 1.5);*/

	/*Transformation Inverse */

	initMatrix(&temp);
	initMatrix(&temp21);
	initMatrix(&temp22);
	initMatrix(&temp23);
	initMatrix(&temp3);


	if(translation!=NULL){
		g3x_MakeTranslationXYZ(temp.c, -translation[0],-translation[1],-translation[2]);
		/*g3x_ProdHMat(temp.c, outputNode->Mi.c,outputNode->Mi.c);*/
		g3x_ProdHMat(outputNode->Mi.c,temp.c, outputNode->Mi.c);
	}
	if(rotation!=NULL){
		if(rotation[0]!=0.){
			g3x_MakeRotationX(temp21.c, -rotation[0]);
			/*g3x_ProdHMat(temp21.c,outputNode->Mi.c,outputNode->Mi.c);*/
			g3x_ProdHMat(outputNode->Mi.c,temp21.c,outputNode->Mi.c);
		}
		if(rotation[1]!=0.){
			g3x_MakeRotationY(temp22.c,-rotation[1]);
			/*g3x_ProdHMat(temp22.c,outputNode->Mi.c,outputNode->Mi.c);*/
			g3x_ProdHMat(outputNode->Mi.c,temp22.c,outputNode->Mi.c);
		}

		if(rotation[2]!=0.){
			g3x_MakeRotationZ(temp23.c,-rotation[2]);
			/*g3x_ProdHMat(temp23.c,outputNode->Mi.c,outputNode->Mi.c);*/
			g3x_ProdHMat(outputNode->Mi.c,temp23.c,outputNode->Mi.c);
		}
	}

	if(homothetie!=NULL){

		g3x_MakeHomothetieXYZ(temp3.c, (double)1/homothetie[0],(double)1/homothetie[1],(double)1/homothetie[2]);
		/*g3x_ProdHMat(temp3.c,outputNode->Mi.c,outputNode->Mi.c);*/
		g3x_ProdHMat(outputNode->Mi.c,temp3.c,outputNode->Mi.c);
	}

}







Shape chassis;
static Shape *ptr_chassis=&chassis;

Shape tourelle;
static Shape *ptr_tourelle=&tourelle;

Shape canon;
static Shape *ptr_canon=&canon;

Shape roueGauche;
static Shape *ptr_roueGauche=&roueGauche;

Shape roueDroite;
static Shape *ptr_roueDroite=&roueDroite;

struct Node scene;
struct Node *ptr_sc= &scene;


struct Node n1;
struct Node *ptr_n1= &n1;
struct Node n2;
struct Node *ptr_n2= &n2;
struct Node n3;
struct Node *ptr_n3= &n3;
struct Node n4;
struct Node *ptr_n4= &n4;
struct Node n5;
struct Node *ptr_n5= &n5;
struct Node n6;
struct Node *ptr_n6= &n6;
struct Node n7;
struct Node *ptr_n7= &n7;
struct Node n8;
struct Node *ptr_n8= &n8;




void Init(void){

	InitCanonical();

	ptr_currMat =currMat.c;
	ptr_currMat=malloc(16*sizeof(double)); 
	/*R0[0]=0;
	R0[1]=0;  
	R0[2]=0;
	ptr_currRep= &R0;*/
	memset(ptr_currMat, 0, 16*sizeof(double));
	g3x_MakeIdentity(ptr_currMat);
	/*glMatrixMode(GL_MODELVIEW);
	glGetDoublev( GL_MODELVIEW, ptr_currMat);
*/
	/*pave*/
	chassis.ID=0;
	/*sphere*/
	/*s1.ID=1;*/
	/*cylindre*/
	tourelle.ID=2;
	canon.ID=2;
	/*tore*/
	roueGauche.ID=3;
	roueDroite.ID=3;
	/*ressort*/
	/*r1.ID=4;*/


	InitializeShape(ptr_chassis);
	InitializeShape(ptr_tourelle);
	InitializeShape(ptr_canon);
	InitializeShape(ptr_roueGauche);
	InitializeShape(ptr_roueDroite);


/*initScene(ptr_sc);*/




/*tourelle*/
	ptr_n3->shapes=(Shape *)malloc(1*sizeof(Shape));
	ptr_n3->shapesNo=1;
	ptr_n3->sonsNo=0;
	ptr_n3->type=0;
	ptr_n3->shapes[0]=tourelle;
	initNodeMatrix(ptr_n3);

/*Canon*/
	ptr_n4->shapes=(Shape *)malloc(1*sizeof(Shape));
	ptr_n4->shapesNo=1;
	ptr_n4->sonsNo=0;
	ptr_n4->type=0;
	ptr_n4->shapes[0]=canon;
	initNodeMatrix(ptr_n4);





/***************/


	/*roue gauche*/
	ptr_n5->shapes=(Shape *)malloc(1*sizeof(Shape));
	ptr_n5->shapesNo=1;
	ptr_n5->sonsNo=0;
	ptr_n5->type=0;
	ptr_n5->shapes[0]=roueGauche;
	initNodeMatrix(ptr_n5); 


	/*roue droite*/
	ptr_n6->shapes=(Shape *)malloc(1*sizeof(Shape));
	ptr_n6->shapesNo=1;
	ptr_n6->sonsNo=0; 
	ptr_n6->type=0;
	ptr_n6->shapes[0]=roueDroite;
	initNodeMatrix(ptr_n6);



/***************/


/*Chassis */
	ptr_n8->shapes=(Shape *)malloc(1*sizeof(Shape));
	ptr_n8->shapesNo=1;
	ptr_n8->sonsNo=0;
	ptr_n8->type=0;
	ptr_n8->shapes[0]=chassis;
	initNodeMatrix(ptr_n8);




/***************************************/

/* tourelle+ canon*/
	ptr_n1->nodes=(Node *)malloc(2*sizeof(Node));
	ptr_n1->sonsNo=2;
	ptr_n1->shapesNo=0;
	ptr_n1->type=2;
	ptr_n1->nodes[0]=n3;
	ptr_n1->nodes[1]=n4;
	initNodeMatrix(ptr_n1);

/*  roue gauche + roue droite*/ 
	ptr_n2->nodes=(Node *)malloc(2*sizeof(Node));
	ptr_n2->shapesNo=0;
	ptr_n2->sonsNo=2;
	ptr_n2->type=2;
	ptr_n2->nodes[0]=n5;
	ptr_n2->nodes[1]=n6;
	initNodeMatrix(ptr_n2);


/* Chassis + autres */
	ptr_n7->nodes=(Node *)malloc(1*sizeof(Node));
	ptr_n7->sonsNo=1;
	ptr_n7->shapesNo=0; 
	ptr_n7->type=2;
	ptr_n7->nodes[0]=n8;
	initNodeMatrix(ptr_n7);



/***************************************/



/*Scene*/
	ptr_sc->nodes=(Node *)malloc(3*sizeof(Node));
	ptr_sc->sonsNo=3;
	ptr_sc->shapesNo=0;
	ptr_sc->type=2;
	ptr_sc->nodes[0]=n7;
	ptr_sc->nodes[1]=n1;       
	ptr_sc->nodes[2]=n2;
	initNodeMatrix(ptr_sc);



/***************************************/



/***************************************************************/





/*Transformation canon et  tourelle*/
	/*double trans[3]={0,0,2};
	double rot[3]= {1.57,0,0};
	double homo[3]={0.1,0.1,10};

	double trans2[3]={0,0,-2};
	double rot2[3]= {-1.57,0,0};
	double homo2[3]={0.1,0.1,10};



/*test*/
/*/§\ PROBLEME QUAND 2 TRANSFORMATION...*/

	/* SUREMENT PARCEQUE LES MATRICES INVERSES SONT FAUSSEES ????**/
	/*  OU EST CE QUE LA SCENE N'EST PAS MISE A JOUR ????? */




	/* MISE A JOUR DE LA SCENE ?**/
	/*HMat id;
	initMatrix(&id);
	UpdateNode(ptr_sc, id.c);*/



	HMat anim;  

/*Ceanon n4 + tourelle n3*/

	double trans_n1[3]={0,0,0.5};

	double homo_n3[3]={1.,1.,0.3};

	double tr_n4[3]={0,1,0.1}; 
	double rot_n4[3]= {1.57,0.,0.};
	double homo_n4[3]={0.25,4,0.25};
	



	MakeTransformation(ptr_n1,trans_n1,NULL,NULL);

	MakeTransformation(ptr_n3,NULL,NULL,homo_n3);

	MakeTransformation(ptr_n4,tr_n4,NULL,NULL);
	MakeTransformation(ptr_n4,NULL,rot_n4,NULL);
	MakeTransformation(ptr_n4,NULL,NULL,homo_n4);
	
	

/*Transformation roue gauche n5+ roue droite n6 */


	
	double trans_n2[3]={0,0,-0.5};
	double rot_n2[3]= {PI/2,0,0};
	double hom_n2[3]={1,0.5,0.3};
	double trans_n5[3]={0,0,-2};
	double trans_n6[3]={0,0,2}; 


	/*MakeTransformation(ptr_n6,trans_n6,NULL,NULL);*/

	MakeTransformation(ptr_n2,NULL,NULL,hom_n2);
	MakeTransformation(ptr_n2,NULL,rot_n2,NULL);
	MakeTransformation(ptr_n2,trans_n2,NULL,NULL);


	
	MakeTransformation(ptr_n5,trans_n5,NULL,NULL);
	MakeTransformation(ptr_n6,trans_n6,NULL,NULL);

	/*initMatrix(&anim); 
	UpdateNode(ptr_sc,anim.c);


/*Chassis */

	double n8_homo[3]={2,1.2,0.8};

	MakeTransformation(ptr_n8,NULL,NULL,n8_homo);
	
		/*HMat anim;*/
	/*initMatrix(&anim); 
	UpdateNode(ptr_sc,anim.c);
*/




	initMatrix(&anim); 
	UpdateNode(ptr_sc,anim.c);







/***************************************************************/

/*
	g3x_MakeTranslationXYZ(ptr_n4->Md.c, 0,-2,0);
	g3x_MakeTranslationXYZ(ptr_n4->Mi.c, 0,2,0);

	g3x_MakeRotationZ(ptr_sc->Md.c, PI/2.0);
	g3x_MakeRotationZ(ptr_sc->Mi.c, -PI/2.0);	


/*
	g3x_MakeTranslationXYZ(ptr_n4->Md.c, 0,-8,0);
	g3x_MakeTranslationXYZ(ptr_n4->Mi.c, 0,8,0);
*/
/*	g3x_MakeRotationX(ptr_sc->Md.c, 1.5);
	g3x_MakeRotationX(ptr_sc->Mi.c, -1.5);
	
	g3x_MakeTranslationXYZ(ptr_n1->Md.c, 0,-4,0);
	g3x_MakeTranslationXYZ(ptr_n1->Mi.c, 0,4,0);

	g3x_MakeTranslationXYZ(ptr_n4->Md.c, 0,-4,0);
	g3x_MakeTranslationXYZ(ptr_n4->Mi.c, 0,4,0);
	
	g3x_MakeRotationX(ptr_n1->Md.c, 0.5);
	g3x_MakeRotationX(ptr_n1->Mi.c, -0.5);
*/



/*Si on veut plusieurs transformations au même noeud, 
On est obligé de passer par des matrices temporaires*/
/*	HMat temp;
	HMat temp2;
	HMat temp3;
	initMatrix(&temp);
	initMatrix(&temp2);
	initMatrix(&temp3);
	g3x_MakeRotationX(temp.c, 0.5);
	g3x_MakeTranslationXYZ(temp2.c,0,-0.4,0);
	g3x_MakeHomothetieXYZ(temp3.c, 1,1,0.5);
	g3x_ProdHMat(temp.c,temp2.c,temp.c);
	g3x_ProdHMat(temp.c,temp3.c,temp.c);
	g3x_ProdHMat(temp.c,ptr_n1->Md.c,ptr_n1->Md.c);



	g3x_MakeRotationX(ptr_n1->Md.c, 1.5);



	initMatrix(&temp);
	initMatrix(&temp2);
	initMatrix(&temp3);
	g3x_MakeRotationX(temp.c, -1.5);
	g3x_MakeTranslationXYZ(temp2.c,0,0.4,0);
	g3x_MakeHomothetieXYZ(temp3.c, 1,1,2);
	g3x_ProdHMat(temp.c,temp2.c,temp.c);
	g3x_ProdHMat(temp.c,temp3.c,ptr_n1->Mi.c);

*/
	HMat temp;
	HMat temp2;
	HMat temp3;
	/*initMatrix(&temp);
	initMatrix(&temp2);
	initMatrix(&temp3);

/*Matrices directes n2 = roue gauche + roue droite */

	/*initMatrix(&temp);
	initMatrix(&temp2);
	initMatrix(&temp3);
	/*g3x_MakeHomothetieXYZ(temp.c, 1,4,0.5);*/
/*	g3x_MakeRotationY(temp.c, -PI/2);
	g3x_MakeTranslationXYZ(temp3.c,0,0,-0.2);
	/*g3x_ProdHMat(temp.c,temp2.c,temp.c);
	g3x_ProdHMat(temp.c,temp3.c,ptr_n2->Md.c);*/
	/*g3x_ProdHMat(ptr_n2->Md.c,temp.c,ptr_n2->Md.c);
	g3x_ProdHMat(ptr_n2->Md.c,temp2.c,ptr_n2->Md.c);
	g3x_ProdHMat(ptr_n2->Md.c,temp3.c,ptr_n2->Md.c);
	

/*Matrices indirectes n2 = roue gauche + roue droite */
/*	initMatrix(&temp);
	initMatrix(&temp2);
	initMatrix(&temp3);
	/*g3x_MakeHomothetieXYZ(temp.c, 1,0.25,2);*/
	/*g3x_MakeRotationY(temp2.c, PI/2);
	g3x_MakeTranslationXYZ(temp3.c,0,0,0.2);
/*	g3x_ProdHMat(temp.c,temp2.c,temp.c);
	g3x_ProdHMat(temp.c,temp3.c,ptr_n2->Mi.c);*/
/*		g3x_ProdHMat(ptr_n2->Mi.c,temp.c,ptr_n2->Mi.c);
	g3x_ProdHMat(ptr_n2->Mi.c,temp2.c,ptr_n2->Mi.c);
	g3x_ProdHMat(ptr_n2->Mi.c,temp3.c,ptr_n2->Mi.c);







/*	


	g3x_MakeHomothetieXYZ(ptr_n2->Md.c, 1,1,0.5);
	g3x_MakeHomothetieXYZ(ptr_n2->Mi.c, 1,1,2); 

*/





	g3x_CreateScrollv_i("n",&n,3,N,1.0," ");
	g3x_CreateScrollv_i("p",&p,3,P,1.0," ");
	g3x_CreateScrollh_d("r",&r,0.1,10.,1.," ");


/*type de scroll 
h horizontal  
v vertical
type du paramètre
i integer
d double 
*/  

}
HMat temp;

void Anim(void)
{

	/*HMat temp;
	HMat temp2;
	initMatrix(&temp);
	initMatrix(&temp2);
	g3x_MakeRotationZ(temp.c, 0.01);
	g3x_MakeRotationZ(temp2.c, -0.01);
	/*Tout rotation*/
/*	g3x_ProdHMat(temp.c, ptr_sc->Md.c, ptr_sc->Md.c);
	g3x_ProdHMat(temp2.c, ptr_sc->Mi.c, ptr_sc->Mi.c);
	/* Tourelle rotation*/
	/*g3x_ProdHMat(temp.c, ptr_n1->Md.c, ptr_n1->Md.c);
	g3x_ProdHMat(temp2.c, ptr_n1->Mi.c, ptr_n1->Mi.c);
*/


	double rot_anim[3]= {0,0,0.01};
	MakeTransformation(ptr_sc,NULL,rot_anim,NULL);
	
	HMat anim;
	initMatrix(&anim); 
	UpdateNode(ptr_sc,anim.c);

/*Affichage matrice*/
	/*DrawNodes(ptr_sc,ptr_currMat);*/
	/*
	int i;

	for (i = 0; i < 16; ++i)
	{
		printf("Matrice directe i = %d -> %f\n", i, ptr_n3->Md.c[i]);
	}
*/
}



/*= FONCTION DE DESSIN PRINCIPALE =*/
static void Dessin(void)
{	


	/*glEnable(GL_LIGHTING);*/

	/*glPushMatrix(); */
	/*glScalef(0.5,0.5,0.5);*/
	/*HMat anim;
	initMatrix(&anim);
	/*g3x_MakeIdentity(anim.c);*/ 

	printf("Entering DrawNodes\n");
	DrawNodes(ptr_sc);
	printf("Exiting DrawNodes\n");

	/*glTranslatef(0.,0.,-10);
	glRotatef(10.,-110.,0.,0.); */ 
	/*g3x_(rouge,ambi,diff,spec,shin,1.);*/




/*
	glPointSize(r);  
		/*glColor4fv(rouge); 
			glColor4fv(orange);  
	g3x_Material(orange,ambi, diff,spec,shin,1.);  
*/

/* On dessine la sphere*/
	/*glPopMatrix();     
	glPushMatrix();      
		glScalef(2.5,2.5,2.5);  
		glScalef(0.5,0.5,0.5);  

	DrawShape(ptr_s1);
	/*test(ptr_s1); 
	test(ptr_s1);test(ptr_s1);test(ptr_s1 );test(ptr_s1);test(ptr_s1);test(ptr_s1);test(ptr_s1);test(ptr_s1);
  
	DrawShape(ptr_s1);
*/
/* On dessine le Pave*/
	/*glPopMatrix();
	glPushMatrix();
	/*glTranslatef(-3.,0.,-1); */
	/*glScalef(2.5,2.5,2.5); 
	DrawShape(ptr_p1);
*/ 

/* On dessine le Cylindre 
	glPopMatrix();  
	glPushMatrix();
	glTranslatef(5.,0.,-1);
	glScalef(2.5,2.5,2.5); 
	DrawShape(ptr_c1);
*/
/* On dessine le Tore*/
	/*glPopMatrix();
	glPushMatrix();
	glTranslatef(3.,3.,-1); 
	glScalef(0.3,.3,0.3); 
	DrawShape(ptr_roueGauche,anim) ;*/

/* On dessine le Ressort*/
/*	glTranslatef(0.,-5.,-1);
	/*printf("%d\n",n1.size );*/
/*	DrawShape(ptr_r1); 

 
	glTranslatef(-5.,-5.,-5);
*/ 



} 

/*=    ACTION A EXECUTER EN SORTIE   =*/
/*= libération de mémoire, nettoyage =*/ 
/*= -> utilise la pile de <atexit()> =*/
static void Exit(void)
{ 
  /* rien à faire ici puisqu'il n'y a pas d'allocation dynamique */
	fprintf(stdout,"\nbye !\n");
} 

/*= action : variation de couleur =*/ 
static void action1(void)
{ 
	rouge[0]-=0.01;  rouge[ 1]+=0.01;
	vert[1] -=0.01;  vert[2] +=0.01;  
	bleu[2] -=0.01;  bleu[0] +=0.01;   
} 
/*= action : variation de couleur =*/
static void action2(void)
{ 
	rouge[0]+=0.01;  rouge[1]-=0.01;
	vert[1] +=0.01;  vert[2] -=0.01;  
	bleu[2] +=0.01;  bleu[0] -=0.01;
} 

/*= action : affiche les parametre camera dans le terminal =*/
static void camera_info(void)
{
	G3Xcamera* cam=g3x_GetCamera();
	fprintf(stderr,"position (x:%lf,y:%lf,z:%lf)\n",(*cam->pos)[0],(*cam->pos)[1],(*cam->pos)[2]);
	fprintf(stderr,"cible    (x:%lf,y:%lf,z:%lf)\n",(*cam->tar)[0],(*cam->tar)[1],(*cam->tar)[2]);
	fprintf(stderr,"coord. spheriques (d:%lf,theta:%lf,phi:%lf)\n",cam->dist,cam->theta,cam->phi);
}

int main(int argc, char** argv)
{  

  /* initialisation de la fenêtre graphique et paramétrage Gl */
	g3x_InitWindow(*argv,768,512);
	g3x_SetInitFunction(Init);
	/* paramètres caméra */
  /* param. géométrique de la caméra. cf. gluLookAt(...) */
	g3x_SetPerspective(40.,100.,1.);
  /* position, orientation de la caméra */
	g3x_SetCameraSpheric(0.25*PI,+0.25*PI,6.,(G3Xpoint){0.,0.,0.});

  /* fixe les param. colorimétriques du spot lumineux */
	/* lumiere blanche (c'est les valeurs par defaut)   */	
	g3x_SetLightAmbient (1,1.,1.);
	g3x_SetLightDiffuse (1.,1.,1.);
	g3x_SetLightSpecular(1.,1.,1.);

  /* fixe la position et la direction du spot lumineux */
	/* (c'est les valeurs par defaut)                    */	
	g3x_SetLightPosition (0.,0.,10.);
	g3x_SetLightDirection( 0, 0, -1);  


  /* définition des fonctions */
  g3x_SetExitFunction(Exit  );     /* la fonction de sortie */
  g3x_SetDrawFunction(Dessin);     /* la fonction de Dessin */
	g3x_SetAnimFunction(Anim);


	/* JUSTE POUT ILLUSTRATION DU TRACEUR D'ALLOC EN COMPIL DEGUG */
	void* ptr=malloc(1);

	/* boucle d'exécution principale */
	return g3x_MainStart();
  /* rien après ça */  
}
