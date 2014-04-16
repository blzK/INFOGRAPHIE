/* ===============================================================
  E.Incerti - Université de Marne-la-Vallée - incerti@univ-mlv.fr 
  ============================================================= */

#include <stdio.h>
#include <g3x.h>




#define N 1000
#define P 1000
#define T 1
  #define U 50

  typedef struct{
  	double c[16];
  } HMat;

  typedef struct Shape
  {
	G3Xpoint *vrtx;/*pointeurs vers les tableaux du vertex canonique*/
	G3Xvector *norm;/*pointeurs vers les tableaux du normales canonique*/
	HMat Md, Mi, Mn; /*Matrices 4x4 directe, inverse, normale*/

	G3Xcolor col; /*Couleur*/
  	int ID; /*type*/
	double ambi, diff, spec, shine, alpha; /*materiau*/
  } Shape;



  typedef struct Node{
  	struct Node * nodes;
  	struct Shape * shapes;
  	int type;
  	int size;
  } Node;


  void initScene(struct Node * str){

  }




/*node={shapes};*/
  /*
Nous allons créer une struct Obj qui contient les données.
Puis nous allons initialiser cette structure avec une méthode différente Init qui va retourner un pointeur vers la structure.
Puis nous allons appeller une méthode Draw qui va dessiner notre structure.

  */


static G3Xcolor orange={0.8,0.6,0.0,0.0};
static int n=100,p=100; /*tailles utiles, n parallèles, p méridiens*/
static double r=1;


/* des couleurs prédéfinies */  
static G3Xcolor rouge  ={1.0,0.0,0.0};
static G3Xcolor jaune  ={1.0,1.0,0.0};
static G3Xcolor vert   ={0.0,1.0,0.0};
static G3Xcolor cyan   ={0.0,1.0,1.0};
static G3Xcolor bleu   ={0.0,0.0,1.0};
static G3Xcolor magenta={1.0,0.0,1.0};
/* paramètres géométriques */
static double angle= 0.00;
static double rayon= 0.66;
/* paramètres de lumière/matière */
static double alpha= 0.5;
static double ambi = 0.4;
static double diff = 0.2;
static double spec = 1;/*0.4;*/
static double shin = 1;/*0.5;*/


#define MAXCOL 25
static G3Xcolor colmap[MAXCOL];

static G3Xvector W={1.,2.,3.};
static double    b=0.1;



Shape * InitializeRessort(Shape * str){

	int i,j;
	double a=2*PI/N;
  	double b=2*PI/P;/*double b=PI/P;*/
	/*double r=1;*/
	str->vrtx=malloc(2*N*P*sizeof(G3Xpoint));
	str->norm=malloc(2*N*P*sizeof(G3Xvector));
	memset(str->vrtx, 20,2*N*P*sizeof(G3Xpoint));
	memset(str->norm, 20,2*N*P*sizeof(G3Xvector));
	G3Xpoint *vt=str->vrtx;
	for(i=0;i<2*N;i++)
	{

		for (j=0;j<P;j++)
		{
			(*vt)[0]=(3*r+r*cos(j*a))*(cos(i*b));
			(*vt)[1]=(3*r+r*cos(j*a))*sin(i*b);
			(*vt)[2]=i*a+r*sin(j*a)-N*a/2;
			vt++;
		}
	}
	return str;
}


Shape * InitializeTore(Shape *str){

	int i,j;
	double a=2*PI/N;
  	double b=2*PI/P;/*double b=PI/P;*/
	/*double r=1;*/
	str->vrtx=malloc(N*P*sizeof(G3Xpoint));
	str->norm=malloc(N*P*sizeof(G3Xvector));
	memset(str->vrtx, 0,N*P*sizeof(G3Xpoint));
	memset(str->norm, 0,N*P*sizeof(G3Xvector)/4);
	G3Xpoint *vt=str->vrtx;
	G3Xvector *vn=str->norm;
	G3Xpoint *ptemp[4];


	for(i=0;i<=N;i++)
	{

		for (j=0;j<=P;j++)
		{
			(*vt)[0]=(3*r+r*cos(j*a))*(cos(i*b));
			(*vt)[1]=(3*r+r*cos(j*a))*sin(i*b);
			(*vt)[2]=r*sin(j*a);

			ptemp[i%4]=vt;

			if(i%4==0){
				/*printf("%d %d %d \n", ptemp[0][0],ptemp[1][1],ptemp[2][1]);*/
				/**/G3Xprodvect3point((*vn),ptemp[0],ptemp[1],ptemp[2]);

				vn++;
			}

			vt++;
		}
	}
	return str;
}



Shape * InitializeSphere(Shape * str){

	int i,j;
	double a=2*PI/N;
	double b=PI/P;

	str->vrtx=malloc(N*P*sizeof(G3Xpoint));
	str->norm=malloc(N*P*sizeof(G3Xvector));
	memset(str->vrtx, 0,N*P*sizeof(G3Xpoint));
	memset(str->norm, 0,N*P*sizeof(G3Xvector));
	G3Xvector *vn=str->norm;
	G3Xpoint *vt=str->vrtx;
	for(i=0;i<=N;i++)
	{

		for (j=0;j<=P;j++)
		{
			(*vt)[0]=r*cos(i*a)*sin(j*b);
			(*vt)[1]=r*sin(i*a)*sin(j*b);
			(*vt)[2]=r*cos(j*b);

/*normale sphere*/
			(*vn)[0]=r*cos(i*a);
			(*vn)[1]=r*sin(i*a);
			(*vn)[2]=r*cos(j*b);

			vn++;
			vt++;
		}
	}
	return str;
}

Shape * InitializeCylindre(Shape * str){

	int i,j;
	double a=2*PI/N;
	double b=PI/P;
	str->vrtx=malloc(N*P*sizeof(G3Xpoint));
	str->norm=malloc(N*P*sizeof(G3Xvector));
	memset(str->vrtx, 0,N*P*sizeof(G3Xpoint));
	memset(str->norm, 0,N*P*sizeof(G3Xvector));
	G3Xpoint *vt=str->vrtx;
	G3Xvector *vn=str->norm;
	
	for(i=0;i<=N;i++)
	{

		for (j=0;j<=P;j++)
		{

			(*vt)[0]=r*cos(i*a);
			(*vt)[1]=r*sin(i*a);
			(*vt)[2]=j*b;	

			(*vn)[0]=cos(i*a);
			(*vn)[1]=sin(i*a);
			(*vn)[2]=0;

			vn++;
			vt++;
		}

	}
	return str;
}


Shape * InitializePave(Shape * str){

	int i,j;
	double a=2*PI/N;
	double b=2*PI/P;

	str->vrtx=malloc(8*sizeof(G3Xpoint));
	str->norm=malloc(8*sizeof(G3Xvector));
	memset(str->vrtx, 0,8*sizeof(G3Xpoint));
	memset(str->norm, 0,8*sizeof(G3Xvector));
	G3Xpoint *v2=str->vrtx;

/*PAVE*/

	(*v2)[0]=(-1)*T/(2.0f);
	(*v2)[1]=(-1)*T/(2.0f);
	(*v2)[2]=0;
	v2++;

	(*v2)[0]=T/2.0f;
	(*v2)[1]=-T/2.0f;
	(*v2)[2]=0;
	v2++;

	(*v2)[0]=T/2.0f;
	(*v2)[1]=T/2.0f;
	(*v2)[2]=0;
	v2++;

	(*v2)[0]=-T/2.0f;
	(*v2)[1]=T/2.0f;
	(*v2)[2]=0;
	v2++;

	(*v2)[0]=-T/2.0f;
	(*v2)[1]=-T/2.0f;
	(*v2)[2]=-T/2.0f;
	v2++;

	(*v2)[0]=T/2.0f;
	(*v2)[1]=-T/2.0f;
	(*v2)[2]=-T/2.0f;
	v2++;

	(*v2)[0]=T/2.0f;
	(*v2)[1]=T/2.0f;
	(*v2)[2]=-T/2.0f;
	v2++;

	(*v2)[0]=-T/2.0f;
	(*v2)[1]=T/2.0f;
	(*v2)[2]=-T/2.0f;

	return str;
}

void DrawPave(Shape * str){

	int i,j,k,N2,P2;
	i=0;
	j=0;
	k=0;

	int stepn=N/n; int stepp=P/p;

	/*SQUELETTE PAVE*/
	glBegin(GL_POINTS);
	g3x_Material(bleu,ambi,diff,spec,shin,1.);

	for(i=0;i<3;i++){

		for(j=0;j<4;j++){
			glVertex3dv(str->vrtx[i*3+j]);

		}
	}
	glEnd();

/*TEXTURE PAVE*/

	glBegin(GL_QUADS);
		/*glColor4fv(bleu);*/

	g3x_Material(bleu,ambi,diff,spec,shin,1.);

	for(i=0;i<8;i++){
		glVertex3dv(str->vrtx[i]);
		glNormal3dv(str->norm[i]);
	}
	for(i=0;i<4;i++){
		glVertex3dv(str->vrtx[i]);
		glNormal3dv(str->norm[i]);
		glVertex3dv(str->vrtx[i+1]);
		glNormal3dv(str->norm[i+1]);
		glVertex3dv(str->vrtx[i+4]);
		glNormal3dv(str->norm[i+4]);
		glVertex3dv(str->vrtx[i+3]);
		glNormal3dv(str->norm[i+3]);

	}
	glEnd();

}

void DrawSphere(Shape * str){

	int i,j,k,N2,P2;
	i=0;
	j=0;
	k=0;

	int stepn=N/n; int stepp=P/p;

	/*SQUELETTE SPHERE*/
	glBegin(GL_POINTS);

	for(i=0;i<N;i+=stepn){

		for(j=0;j<P;j+=stepp){
			k=i*P+j;

			/*printf("\n %f %f %f !\n",str->vrtx[k][0],str->vrtx[k][1], str->vrtx[k][2]);*/

			glVertex3dv(str->vrtx[k]);
			

		}

	}
	glEnd();

	/*TEXTURE SPHERE*/
	glBegin(GL_QUADS);

	for(i=0;i<N;i+=stepn){
		for(j=0;j<P;j+=stepp){
			glVertex3dv(str->vrtx[i*N+j]);
			glVertex3dv(str->vrtx[i*N+j+stepp]);
			glVertex3dv(str->vrtx[(i+stepn)*N+j+stepp]);
			glVertex3dv(str->vrtx[(i+stepn)*N+j]);

			glNormal3dv(str->norm[i*N+j]);
			glNormal3dv(str->norm[i*N+j+stepp]);
			glNormal3dv(str->norm[(i+stepn)*N+j+stepp]);
			glNormal3dv(str->norm[(i+stepn)*N+j]);

		}


	}
	glEnd();

}


void DrawRessort(Shape * str){

	int i,j,k;
	i=0;
	j=0;
	k=0;

	int stepn=N/n; int stepp=P/p;

	/*SQUELETTE RESSORT*/
	glBegin(GL_POINTS);

	for(i=0;i<N;i+=stepn){

		for(j=0;j<P;j+=stepp){
			k=i*P+j;

			/*printf("\n %f %f %f !\n",str->vrtx[k][0],str->vrtx[k][1], str->vrtx[k][2]);*/

			glVertex3dv(str->vrtx[k]);


		}

	}
	glEnd();

	/*TEXTURE RESSORT*/
	glBegin(GL_QUADS);

	for(i=0;i<2*N-stepn;i+=stepn){
		for(j=0;j<P;j+=stepp){
			glVertex3dv(str->vrtx[i*N+j]);
			glVertex3dv(str->vrtx[i*N+j+stepp]);
			glVertex3dv(str->vrtx[(i+stepn)*N+j+stepp]);
			glVertex3dv(str->vrtx[(i+stepn)*N+j]);

			glNormal3dv(str->norm[i*N+j]);
			glNormal3dv(str->norm[i*N+j+stepp]);
			glNormal3dv(str->norm[(i+stepn)*N+j+stepp]);
			glNormal3dv(str->norm[(i+stepn)*N+j]);

		}
	}
	glEnd();

}
void DrawTore(Shape * str){

	int i,j,k;
	i=0;
	j=0;
	k=0;

	int stepn=N/n; int stepp=P/p;

	/*SQUELETTE TORE*/
	glBegin(GL_POINTS);

	for(i=0;i<N;i+=stepn){

		for(j=0;j<P;j+=stepp){
			k=i*P+j;

			/*printf("\n %f %f %f !\n",str->vrtx[k][0],str->vrtx[k][1], str->vrtx[k][2]);*/

			glVertex3dv(str->vrtx[k]);


		}

	}
	glEnd();

	/*TEXTURE TORE*/
	glBegin(GL_QUADS);

	for(i=0;i<N;i+=stepn){
		for(j=0;j<P;j+=stepp){
			glVertex3dv(str->vrtx[i*N+j]);
			glVertex3dv(str->vrtx[i*N+j+stepp]);
			glVertex3dv(str->vrtx[(i+stepn)*N+j+stepp]);
			glVertex3dv(str->vrtx[(i+stepn)*N+j]);

			if(i%4){

				glNormal3dv(str->norm[i*N+j]);

			}

		}

	}

	glColor4fv(rouge);
	g3x_Material(rouge,ambi,diff,spec,shin,1.);
	i=0;

	for(j=0;j<P;j+=stepp){
		glVertex3dv(str->vrtx[N*P+j]);
		glVertex3dv(str->vrtx[N*P+j+stepp]);
		glVertex3dv(str->vrtx[(stepn)*N+j+stepp]);
		glVertex3dv(str->vrtx[(stepn)*N+j]);
	}

	glEnd();


}

void DrawCylindre(Shape * str){

	int i,j,k,N2,P2;
	i=0;
	j=0;
	k=0;
	/*int n=100;
	int p=100; */
	int stepn=N/n; int stepp=P/p;

	/*SQUELETTE TORE*/
	glBegin(GL_POINTS);

	for(i=0;i<N;i+=stepn){

		for(j=0;j<P;j+=stepp){
			k=i*N+j;

			/*printf("\n %f %f %f !\n",str->vrtx[k][0],str->vrtx[k][1], str->vrtx[k][2]);*/

			glVertex3dv(str->vrtx[k]);
			glNormal3dv(str->vrtx[k]);

		}

	}
	glEnd();

	/*TEXTURE CYLINDRE*/
	glBegin(GL_QUADS);

	for(i=0;i<N;i+=stepn){
		for(j=0;j<P;j+=stepp){
			glVertex3dv(str->vrtx[i*N+j]);
			glVertex3dv(str->vrtx[i*N+j+stepp]);
			glVertex3dv(str->vrtx[(i+stepn)*N+j+stepp]);
			glVertex3dv(str->vrtx[(i+stepn)*N+j]);
/*				glNormal3dv(str->norm[i*N+j]);
				glNormal3dv(str->norm[(i+stepn)*N+j+stepp]);
				glNormal3dv(str->norm[(i+stepn)*N+j]);*/

			}

		}
		for(i=0;i<N;i+=stepn){

			for(j=0;j<P;j+=stepp){
				k=i*N+j;
				
				glNormal3dv(str->vrtx[k]);

			}

		}

		glColor4fv(rouge);
		g3x_Material(vert,ambi,diff,spec,shin,1.);
		i=0;

		for(j=0;j<P;j+=stepp){
			glVertex3dv(str->vrtx[N*P+j]);
			glVertex3dv(str->vrtx[N*P+j+stepp]);
			glVertex3dv(str->vrtx[(stepn)*N+j+stepp]);
			glVertex3dv(str->vrtx[(stepn)*N+j]);
		}


		glEnd();

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
		/*glTranslatef(5.,5.,-1);*/
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
			g3x_Material(orange,ambi,diff,spec,shin,1.);
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
		printf("Entering DrawLeaf\n");
		size=(str->size);
		printf("%d\n", size);

		printf("shapes \n");
		for(i=0;i<size;i++){
			DrawShape(&(str->shapes)[i]);
		}
	}

	void DrawNodes(Node * str){
		int size,i;

		size=str->size;
		printf("I'm a Node my size is %d my type is %d\n",size, str->type );

		if(str->type==0){
			printf("I'm a leaf %d\n",size );
			DrawLeaf(str);
		}
	else if(str->type==1){/*Si c'est un noeud*/
		printf("Go to son \n");
		Node *son;
		for(i=0;i<(str->size);i++){
			printf("test\n");
			son=&((str->nodes)[i]);
			printf("looking son  %d type %d\n", i, son->type );
			DrawNodes(son);

		}
	}
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

void exploreTree(){

}

Shape p1;
static Shape *ptr_p1=&p1;

Shape s1;
static Shape *ptr_s1=&s1;

Shape c1;
static Shape *ptr_c1=&c1;

Shape t1;
static Shape *ptr_t1=&t1;

Shape r1;
static Shape *ptr_r1=&r1;

struct Node scene;
struct Node *ptr_sc= &scene;
struct Node n1;
struct Node *ptr_n1= &n1;

void Init(void){
	/*pave*/
	p1.ID=0;
	/*sphere*/
	s1.ID=1;
	/*cylindre*/
	c1.ID=2;
	/*tore*/
	t1.ID=3;
	/*ressort*/
	r1.ID=4;


	InitializeShape(ptr_p1);
	InitializeShape(ptr_s1);
	InitializeShape(ptr_c1);
	InitializeShape(ptr_t1);
	InitializeShape(ptr_r1);


/*initScene(ptr_sc);*/
	ptr_n1->shapes=(Shape *)malloc(5*sizeof(Shape));
	ptr_n1->size=5;
	ptr_n1->type=0;
	ptr_n1->shapes[0]=p1;
	ptr_n1->shapes[1]=s1;
	ptr_n1->shapes[2]=c1;
	ptr_n1->shapes[3]=t1;
	ptr_n1->shapes[4]=r1;

	ptr_sc->nodes=(Node *)malloc(1*sizeof(Node));
	ptr_sc->size=1;
	ptr_sc->type=1;
	ptr_sc->nodes[0]=n1;



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
void Anim(void)
{
}

/* flag d'affichag/masquage */
static bool FLAG_TEAPOT=true;
static bool FLAG_TORUS =true;
static bool FLAG_CONE  =true;
static bool FLAG_ICOS  =true;

/*= FONCTION DE DESSIN PRINCIPALE =*/
static void Dessin(void)
{	
	glEnable(GL_LIGHTING);
	
	glPushMatrix();
	glScalef(0.7,.7,0.7);
	DrawNodes(ptr_sc);
	glTranslatef(0.,0.,-10);
	glRotatef(10.,-110.,0.,0.);
	g3x_Material(rouge,ambi,diff,spec,shin,1.);
	int stepn=N/n, stepp=P/p;
	int i,j;

	glPointSize(r);
	glColor4fv(rouge);
	
	int k;

	glColor4fv(orange);
	g3x_Material(orange,ambi,diff,spec,shin,1.);


/* On dessine la sphere*/
	glPopMatrix();
	glPushMatrix();
	glTranslatef(3.,0.,-1);
	/*test(ptr_s1);
	test(ptr_s1);test(ptr_s1);test(ptr_s1);test(ptr_s1);test(ptr_s1);test(ptr_s1);test(ptr_s1);test(ptr_s1);

	DrawShape(ptr_s1);
*/
/* On dessine le Pave*/
/*	glPopMatrix();
	glPushMatrix();
	glTranslatef(-3.,0.,-1);
	DrawShape(ptr_p1);

/* On dessine le Cylindre*/
/*	glPopMatrix();
	glPushMatrix();
	glTranslatef(5.,0.,-1);
	DrawShape(ptr_c1);

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
	rouge[0]-=0.01;  rouge[1]+=0.01;
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
	g3x_SetLightPosition (10.,10.,10.);
	g3x_SetLightDirection( 0.1, 0.5, 0.7);  


  /* définition des fonctions */
  g3x_SetExitFunction(Exit  );     /* la fonction de sortie */
  g3x_SetDrawFunction(Dessin);     /* la fonction de Dessin */
	g3x_SetAnimFunction(NULL);


	/* JUSTE POUT ILLUSTRATION DU TRACEUR D'ALLOC EN COMPIL DEGUG */
	void* ptr=malloc(1);

	/* boucle d'exécution principale */
	return g3x_MainStart();
  /* rien après ça */
}
