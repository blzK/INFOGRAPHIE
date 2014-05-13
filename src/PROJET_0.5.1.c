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
	int shapesNo; /*Nombre de fils*/
	int sonsNo;
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
	int i;

	for (i = 0; i < 16; ++i)
	{
		printf("Matrice directe i = %d -> %f\n", i, str->Md.c[i]);
	}

	/*g3x_MPrintHMat(*(str->Md.c));*/

}

void initMatrix(HMat * mat){
	mat->c=malloc(16*sizeof(double));

	memset(mat->c, 0,16*sizeof(double));
	
	g3x_MakeIdentity(mat->c);

	/*g3x_MPrintHMat(str->Md.c);*/

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

void DrawShape(Shape * str){
	glColor4fv(orange);
	/*G3Xpoint R1;*/

	/*g3x_ProdHMat(ptr_currMat, str->Md.c, ptr_currMat);*/
/*g3x_ProdHMatPoint(ptr_currMat, str->Md.c, ptr_currMat)*/
	/*g3x_ProdHMatPoint(ptr_currMat, *ptr_currRep, R1);*/

	/*UpdateShape(str,ptr_currMat);*/

	printf("drawing shape %d\n", str->ID);
	switch (str->ID){
		case 0: 
		g3x_Material(vert,ambi,diff,spec,shin,1.);
		DrawPave(str,ptr_currMat);
		break;
		case 1:
		g3x_Material(rouge,ambi,diff,spec,shin,1.);
		DrawSphere(str,ptr_currMat);
		break;
		case 2:
		g3x_Material(orange,ambi,diff,spec,shin,1.);
		DrawCylindre(str,ptr_currMat);
		break;
		case 3:
		g3x_Material(jaune,ambi,diff,spec,shin,1.);
		DrawTore(str,ptr_currMat);
		break;
		case 4:
		g3x_Material(cyan,ambi,diff,spec,shin,1.);
		DrawRessort(str,ptr_currMat);   
		break;
	}        
}

void DrawLeaf(Node * str){ 
	int i,size;
	printf("Entering DrawLeaf\n");
	size=(str->shapesNo);

	printf("%d\n", size);
/*Application de la matrice directe*/
	/*glPushMatrix();*/


	g3x_ProdHMat(ptr_currMat, str->Md.c, ptr_currMat);


/*Dessin*/
	printf("shapes \n");
	for(i=0;i<size;i++){
		/*UpdateShape(&(str->shapes)[i],ptr_currMat);*/
		DrawShape(&(str->shapes)[i]);
	}

/*Application de la matrice inverse*/
	g3x_ProdHMat(ptr_currMat,str->Mi.c,ptr_currMat);


}

void DrawsubNode(Node * str){

}


void DrawNodes(Node * str){
	int size,i;

	size=str->sonsNo;


	if(str->type==0){
		printf("I'm an object %d\n",size );
		DrawLeaf(str);

	}
else if(str->type==1){/*Si c'est un macro-object*/
	printf("I'm a SubNode my size is %d my type is %d\n",size, str->type );
	printf("Drawing macro-object %d\n",size );
/*Application de la matrice directe*/
	/*g3x_ProdHMat(ptr_currMat, str->Md.c, ptr_currMat);*/
	g3x_ProdHMat( str->Md.c,ptr_currMat, ptr_currMat);

/*Dessin*/
	printf("shapes \n");
	for(i=0;i<str->shapesNo;i++){
		DrawShape(&(str->shapes)[i]);
	}
/*Dessine ses fils*/
	printf("Go to son \n");
	Node *son;
	for(i=0;i<(str->sonsNo);i++){
		printf("test\n");
		son=&((str->nodes)[i]);
		printf("looking son %d type %d\n", i, son->type );
		DrawNodes(son);

	}

/*Application de la matrice inverse*/
/*g3x_ProdHMat(ptr_currMat,str->Mi.c,ptr_currMat);*/
	g3x_ProdHMat(str->Mi.c,ptr_currMat,ptr_currMat);

}
else if(str->type==2){/*Si c'est un noeud*/
printf("I'm a Node my size is %d my type is %d\n",size, str->type );
printf("Go to son \n");
Node *son;

/*Application de la matrice directe*/
	/*g3x_ProdHMat(ptr_currMat, str->Md.c, ptr_currMat);*/
g3x_ProdHMat( str->Md.c,ptr_currMat, ptr_currMat);


for(i=0;i<(str->sonsNo);i++){
	printf("test\n");
	son=&((str->nodes)[i]);
	printf("looking son %d type %d\n", i, son->type );
	DrawNodes(son);
}

/*Application de la matrice inverse*/
/*g3x_ProdHMat(ptr_currMat,str->Mi.c,ptr_currMat);*/
g3x_ProdHMat(str->Mi.c,ptr_currMat,ptr_currMat);
}
}


void DrawNodes_ok(Node * str){
	int size,i;

	size=str->sonsNo;


	if(str->type==0){
		printf("I'm an object %d\n",size );
		DrawLeaf(str);
	}
else if(str->type==1){/*Si c'est un macro-object*/
	printf("I'm a SubNode my size is %d my type is %d\n",size, str->type );
	printf("Drawing macro-object %d\n",size );
/*Application de la matrice directe*/

	g3x_ProdHMat(ptr_currMat, str->Md.c, ptr_currMat);

/*Dessin*/
	printf("shapes \n");
	for(i=0;i<str->shapesNo;i++){
		DrawShape(&(str->shapes)[i]);
	}
/*Dessine ses fils*/
	printf("Go to son \n");
	Node *son;
	for(i=0;i<(str->sonsNo);i++){
		printf("test\n");
		son=&((str->nodes)[i]);
		printf("looking son %d type %d\n", i, son->type );
		DrawNodes(son);

	}

/*Application de la matrice inverse*/
	g3x_ProdHMat(ptr_currMat,str->Mi.c,ptr_currMat);
}
else if(str->type==2){/*Si c'est un noeud*/
printf("I'm a Node my size is %d my type is %d\n",size, str->type );
printf("Go to son \n");
Node *son;
for(i=0;i<(str->sonsNo);i++){
	printf("test\n");
	son=&((str->nodes)[i]);
	printf("looking son %d type %d\n", i, son->type );
	DrawNodes(son);

}
}
}




void UpdateLeaf(Node * str, double * ptr_Mat){ 
	int i,size;
	printf("Entering DrawLeaf\n");
	size=(str->shapesNo);

	printf("%d\n", size);
/*Application de la matrice directe*/
	/*g3x_ProdHMat(ptr_Mat, str->Md.c, ptr_Mat);*/
	g3x_ProdHMat(str->Md.c, ptr_Mat,  ptr_Mat);


/*Dessin*/ 
	printf("shapes \n");
	for(i=0;i<size;i++){ 
		/*UpdateShape(&(str->shapes)[i],ptr_currMat);*/
		UpdateShape(&(str->shapes)[i],ptr_Mat);
	}

/*Application de la matrice inverse*/
	/*g3x_ProdHMat(ptr_Mat,str->Mi.c,ptr_Mat);*/
	g3x_ProdHMat(str->Mi.c,ptr_Mat,ptr_Mat);


}


void UpdateNode(Node * str, double * ptr_Mat){
	int size,i;
	size=str->sonsNo;

	if(str->type==0){
		printf("I'm an object %d\n",size );
		UpdateLeaf(str,ptr_Mat);
	}

else if(str->type==1){/*Si c'est un macro-object*/
	printf("I'm a SubNode my size is %d my type is %d\n",size, str->type );
	printf("Drawing macro-object %d\n",size );
/*Application de la matrice directe*/
	/*g3x_ProdHMat(ptr_Mat, str->Md.c, ptr_Mat);*/
	g3x_ProdHMat(str->Md.c, ptr_Mat,  ptr_Mat);

/*Dessin*/
	printf("shapes \n");
	for(i=0;i<str->shapesNo;i++){
		UpdateShape(&(str->shapes)[i],ptr_Mat);
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

/*Application de la matrice inverse*/
	/*g3x_ProdHMat(ptr_Mat,str->Mi.c,ptr_Mat);*/
	g3x_ProdHMat(str->Mi.c, ptr_Mat,ptr_Mat);

}
else if(str->type==2){/*Si c'est un noeud*/
printf("I'm a Node my size is %d my type is %d\n",size, str->type );
printf("Go to son \n");
Node *son;
/*Application de la matrice directe*/
/*g3x_ProdHMat(ptr_Mat, str->Md.c, ptr_Mat);*/
g3x_ProdHMat(str->Md.c, ptr_Mat,  ptr_Mat);

for(i=0;i<(str->sonsNo);i++){
	printf("test\n");
	son=&((str->nodes)[i]);
	printf("looking son %d type %d\n", i, son->type );
	UpdateNode(son, ptr_Mat);

}

/*Application de la matrice inverse*/
/*g3x_ProdHMat(ptr_Mat,str->Mi.c,ptr_Mat);*/
g3x_ProdHMat(str->Mi.c, ptr_Mat,ptr_Mat);

}

}








/*
Mise à jour des coordonnées après changement des matrices.

Parcours l'arbre, et obtiens les matrices résultantes à chaque feuille.
N0 | sur chacune de ses shapes UpdateShape(MdN0) 
N1 | UpdateShape(MdN0 x MdN1)
N2 | UpdateShape(MdN0 x MdN1 x MdN1)

temp=No;
temp=N0xN1;
*/
/*void UpdateScene(Node * str){

	g3x_MakeIdentity(ptr_currMat);

	int size,i;

	size=str->sonsNo;

	HMat resultMat;
	g3x_ProdHMat(resultMat.c, str->Md.c, resultMat.c);

	if(str->type==0){
		printf("I'm an object %d\n",size );
		
	}
	else if(str->type==1){/*Si c'est un macro-object*/
/*	printf("I'm a SubNode my size is %d my type is %d\n",size, str->type );

	g3x_ProdHMat(ptr_currMat, str->Md.c, ptr_currMat);

/*Dessin*/
/*	printf("shapes \n");
	for(i=0;i<str->shapesNo;i++){
		DrawShape(&(str->shapes)[i]);
	}
/*Dessine ses fils*/
/*	printf("Go to son \n");
	Node *son;
	for(i=0;i<(str->sonsNo);i++){
		printf("test\n");
		son=&((str->nodes)[i]);
		printf("looking son  %d type %d\n", i, son->type );
		DrawNodes(son);

	}

	/*Application de la matrice inverse*/
/*	g3x_ProdHMat(ptr_currMat,str->Mi.c,ptr_currMat);
}
/*	else if(str->type==2){/*Si c'est un noeud*/
/*printf("I'm a Node my size is %d my type is %d\n",size, str->type );
printf("Go to son \n");
Node *son;
for(i=0;i<(str->sonsNo);i++){
	printf("test\n");
	son=&((str->nodes)[i]);
	printf("looking son  %d type %d\n", i, son->type );
	DrawNodes(son);

}
}
}
*/












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

void exploreTree(){

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

void MakeTransformation(Node * outputNode, double translation[3], double rotation[3], double homothetie[3] ){


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
	}

	if(rotation!=NULL){
		g3x_MakeRotationX(temp21.c, rotation[0]);
		g3x_MakeRotationY(temp22.c,rotation[1]);
		g3x_MakeRotationZ(temp23.c,rotation[2]);
	}
	if(homothetie!=NULL){
		g3x_MakeHomothetieXYZ(temp3.c, homothetie[0],homothetie[1],homothetie[2]);
	}

	g3x_ProdHMat(temp.c, outputNode->Md.c,outputNode->Md.c);
	g3x_ProdHMat(temp21.c,outputNode->Md.c,outputNode->Md.c);
	g3x_ProdHMat(temp22.c,outputNode->Md.c,outputNode->Md.c);
	g3x_ProdHMat(temp23.c,outputNode->Md.c,outputNode->Md.c);
	g3x_ProdHMat(temp3.c,outputNode->Md.c,outputNode->Md.c);



	/*g3x_MakeRotationX(ptr_n1->Md.c, 1.5);*/

	initMatrix(&temp);
	initMatrix(&temp21);
	initMatrix(&temp22);
	initMatrix(&temp23);
	initMatrix(&temp3);


	if(translation!=NULL){
		g3x_MakeTranslationXYZ(temp.c, -translation[0],-translation[1],-translation[2]);
	}
	if(rotation!=NULL){
		g3x_MakeRotationX(temp21.c, -rotation[0]);
		g3x_MakeRotationY(temp22.c,-rotation[1]);
		g3x_MakeRotationZ(temp23.c,-rotation[2]);
	}

	if(homothetie!=NULL){

		g3x_MakeHomothetieXYZ(temp3.c, (double)1/homothetie[0],(double)1/homothetie[1],(double)1/homothetie[2]);
	}

	g3x_ProdHMat(temp.c, outputNode->Mi.c,outputNode->Mi.c);
	g3x_ProdHMat(temp21.c,outputNode->Mi.c,outputNode->Mi.c);
	g3x_ProdHMat(temp22.c,outputNode->Mi.c,outputNode->Mi.c);
	g3x_ProdHMat(temp23.c,outputNode->Mi.c,outputNode->Mi.c);
	g3x_ProdHMat(temp3.c,outputNode->Mi.c,outputNode->Mi.c);

}

void Init(void){

	ptr_currMat =currMat.c;
	ptr_currMat=malloc(16*sizeof(double)); 
	/*R0[0]=0;
	R0[1]=0;  
	R0[2]=0;
	ptr_currRep= &R0;*/
	memset(ptr_currMat, 0,16*sizeof(double));
	g3x_MakeIdentity(ptr_currMat);
	/*glMatrixMode(GL_MODELVIEW);
	glGetDoublev( GL_MODELVIEW, ptr_currMat);*/

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

	/*roue droite*/
/*	ptr_n6->shapes=(Shape *)malloc(1*sizeof(Shape));
	ptr_n6->shapesNo=1;
	ptr_n6->sonsNo=0; 
	ptr_n6->type=0;
	ptr_n6->shapes[0]=roueDroite;
	initNodeMatrix(ptr_n6);

	/*route gauche*/
	/*ptr_n5->shapes=(Shape *)malloc(1*sizeof(Shape));
	ptr_n5->shapesNo=1;
	ptr_n5->sonsNo=0;
	ptr_n5->type=0;
	ptr_n5->shapes[0]=roueGauche;
	initNodeMatrix(ptr_n5); 

/*Canon*/
	ptr_n4->shapes=(Shape *)malloc(1*sizeof(Shape));
	ptr_n4->shapesNo=1;
	ptr_n4->sonsNo=0;
	ptr_n4->type=0;
	ptr_n4->shapes[0]=canon;
	initNodeMatrix(ptr_n4);


/*tourelle*/
	ptr_n3->shapes=(Shape *)malloc(1*sizeof(Shape));
	ptr_n3->shapesNo=1;
	ptr_n3->sonsNo=0;
	ptr_n3->type=0;
	ptr_n3->shapes[0]=tourelle;
	initNodeMatrix(ptr_n3);

/*  roue gauche + roue droite*/ 
/*	ptr_n2->shapes=(Shape *)malloc(2*sizeof(Node));
	ptr_n2->shapesNo=0;
	ptr_n2->sonsNo=0;
	ptr_n2->type=2;
	ptr_n2->nodes[0]=n5;
	ptr_n2->nodes[1]=n6;
	/*ptr_n2->shapes[0]=p1;*/
	/*ptr_n2->shapes[1]=s1;
	ptr_n2->shapes[2]=c1;
	ptr_n2->shapes[3]=t1;
	ptr_n2->shapes[4]=r1;*/
	/*initNodeMatrix(ptr_n2);
 


/* tourelle+ canon*/
	ptr_n1->nodes=(Node *)malloc(2*sizeof(Node));
	ptr_n1->sonsNo=2;
	ptr_n1->shapesNo=0; 
	ptr_n1->type=2;
	ptr_n1->nodes[0]=n3;
	ptr_n1->nodes[1]=n4;
	initNodeMatrix(ptr_n1);


/*Chassis*/
	ptr_sc->nodes=(Node *)malloc(1*sizeof(Node));
	ptr_sc->shapes=(Shape *)malloc(1*sizeof(Shape));
	ptr_sc->sonsNo=1;
	ptr_sc->shapesNo=1;
	ptr_sc->type=1;
	ptr_sc->nodes[0]=n1;       
	/*ptr_sc->nodes[1]=n2;*/
	ptr_sc->shapes[0]=chassis;  
	initNodeMatrix(ptr_sc);


/*On fait une translation pour séparer les objets*/


	double trans[3]={0,0,0.4};
	double rot[3]= {1.57,0,0};
	double homo[3]={0.25,0.25,4};


	MakeTransformation(ptr_n4,trans,NULL,NULL);
	MakeTransformation(ptr_n4,NULL,NULL,homo);
	MakeTransformation(ptr_n4,NULL,rot,NULL);


	double n3_homo[3]={2.,2.,1.};
	MakeTransformation(ptr_n3,NULL,NULL,n3_homo);
	




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
	/*HMat temp;
	HMat temp2;
	HMat temp3;
	initMatrix(&temp);
	initMatrix(&temp2);
	initMatrix(&temp3);
	g3x_MakeRotationX(temp.c, 0.5);
	g3x_MakeTranslationXYZ(temp2.c,0,-4,0);
	g3x_MakeHomothetieXYZ(temp3.c, 1,1,0.5);
	g3x_ProdHMat(temp.c,temp2.c,temp.c);
	g3x_ProdHMat(temp.c,temp3.c,temp.c);
	g3x_ProdHMat(temp.c,ptr_n1->Md.c,ptr_n1->Md.c);

	/*g3x_MakeRotationX(ptr_n1->Md.c, 1.5);*/

	/*initMatrix(&temp);
	initMatrix(&temp2);
	initMatrix(&temp3);
	g3x_MakeRotationX(temp.c, -1.5);
	g3x_MakeTranslationXYZ(temp2.c,0,4,0);
	g3x_MakeHomothetieXYZ(temp3.c, 1,1,2);
	g3x_ProdHMat(temp.c,temp2.c,temp.c);
	g3x_ProdHMat(temp.c,temp3.c,ptr_n1->Mi.c);


*/




	


	/*g3x_MakeHomothetieXYZ(ptr_n2->Md.c, 1,1,0.5);
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

	

	HMat temp;
	HMat temp2;
	initMatrix(&temp);
	initMatrix(&temp2);
	g3x_MakeRotationX(temp.c, 0.000001);
	g3x_MakeRotationX(temp2.c, -0.00001);
	g3x_ProdHMat(temp.c, ptr_sc->Md.c, ptr_sc->Md.c);
	g3x_ProdHMat(temp2.c, ptr_sc->Mi.c, ptr_sc->Mi.c);
	UpdateNode(ptr_sc,ptr_currMat);

	/*UpdateShape(&(ptr_n2->shapes[0]),temp.c);*/
	
	



	
	/*initMatrix(&temp);*/
	/*temp=ptr_n1->Md;*/

/*	g3x_MakeRotationX(temp.c, 0.001);
	UpdateShape(&(ptr_n2->shapes[0]),temp.c);
	/*DrawShape(&(ptr_n2->shapes[0]));*/
/*DrawNodes(ptr_sc);*/
	/*g3x_ProdHMat(ptr_currMat, temp.c, ptr_currMat);/*
	g3x_MakeRotationX(temp.c, -1.5);

		


/* bof bof bof*/
	/*g3x_MakeRotationX(temp.c, 0.001);
	g3x_ProdHMat( ptr_n1->Md.c,temp.c, ptr_n1->Md.c);
	g3x_MakeRotationX(temp.c, -0.001);
	g3x_ProdHMat( temp.c,ptr_n1->Mi.c, ptr_n1->Mi.c);

	DrawNodes(ptr_sc);*/

	/*glMatrixMode(GL_MODELVIEW);
	glGetDoublev( GL_MODELVIEW, ptr_currMat);
	glLoadMatrixd(ptr_currMat);*/

}



/*= FONCTION DE DESSIN PRINCIPALE =*/
static void Dessin(void)
{	
	glEnable(GL_LIGHTING);
	
	/*glPushMatrix(); */
	/*glScalef(0.5,0.5,0.5);*/
	DrawNodes(ptr_sc);
	/*glTranslatef(0.,0.,-10);
	glRotatef(10.,-110.,0.,0.); */ 
	g3x_Material(rouge,ambi,diff,spec,shin,1.);


	glPointSize(r);  
	glColor4fv(rouge); 
	

	glColor4fv(orange); 
	g3x_Material(orange,ambi, diff,spec,shin,1.);


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
/*	glPopMatrix();
	glPushMatrix();
	glTranslatef(3.,3.,-1); 
	glScalef(0.3,.3,0.3); 
	DrawShape(ptr_t1);

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