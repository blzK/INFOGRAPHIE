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

  typedef struct
  {
	G3Xpoint *vrtx;/*pointeurs vers les tableaux du vertex canonique*/
	G3Xvector *norm;/*pointeurs vers les tableaux du normales canonique*/
	HMat Md, Mi, Mn; /*Matrices 4x4 directe, inverse, noramle*/
	G3Xcolor col; /*Couleur*/
	double ambi, diff, spec, shine, alpha; /*materiau*/
  } Object;

  typedef struct {

  	G3Xpoint vrtx[2*N*P];
  	G3Xpoint norm[2*N*P];
	G3Xcolor col; /*Couleur*/
	double ambi, diff, spec, shine, alpha; /*materiau*/

  } Ressort;

  typedef struct {

  	G3Xpoint vrtx[N*P];
  	G3Xpoint norm[N*P];
	G3Xcolor col; /*Couleur*/
	double ambi, diff, spec, shine, alpha; /*materiau*/

  } Sphere;

  typedef struct {

  	G3Xpoint vrtx[8];
  	G3Xpoint norm[8];
	G3Xcolor col; /*Couleur*/
	double ambi, diff, spec, shine, alpha; /*materiau*/

  } Pave;

  typedef struct {

  	G3Xpoint vrtx[N*P];
  	G3Xpoint norm[N*P];
	G3Xcolor col; /*Couleur*/
	double ambi, diff, spec, shine, alpha; /*materiau*/

  } Cylindre;




  /*
Nous allons créer une struct Obj qui contient les données.
Puis nous allons initialiser cette structure avec une méthode différente Init qui va retourner un pointeur vers la structure.
Puis nous allons appeller une méthode Draw qui va dessiner notre structure.

  */
static G3Xpoint vrtx[2*N*P];
static G3Xpoint norm[2*N*P];
static G3Xpoint vrtx2[12];
static G3Xpoint norm2[12];

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
static double spec = 0.4;
static double shin = 0.5;


#define MAXCOL 25
static G3Xcolor colmap[MAXCOL];

static G3Xvector W={1.,2.,3.};
static double    b=0.1;



Ressort * InitializeRessort(Ressort *str){

	int i,j;
	double a=2*PI/N;
  	double b=2*PI/P;/*double b=PI/P;*/
	/*double r=1;*/
	memset(str->vrtx, 20,2*N*P*sizeof(G3Xpoint));
	memset(str->norm, 20,2*N*P*sizeof(G3Xvector));
	G3Xpoint *vt=str->vrtx;
	for(i=0;i<2*N;i++)
	{

		for (j=0;j<P;j++)
		{
			(*vt)[0]=(3*r+r*cos(j*a))*(cos(i*b));
			(*vt)[1]=(3*r+r*cos(j*a))*sin(i*b);
			(*vt)[2]=i*a+r*sin(j*a);
			vt++;
		}
	}
	return str;
}



Sphere * InitializeSphere(Sphere *str){

	int i,j;
	double a=2*PI/N;
  	double b=PI/P;/*double b=PI/P;*/
	/*double r=1;*/
	memset(str->vrtx, 20,N*P*sizeof(G3Xpoint));
	memset(str->norm, 20,N*P*sizeof(G3Xvector));
	G3Xpoint *vt=str->vrtx;
	for(i=0;i<N;i++)
	{

		for (j=0;j<P;j++)
		{
			(*vt)[0]=r*cos(i*a)*sin(j*b);
			(*vt)[1]=r*sin(i*a)*sin(j*b);
			(*vt)[2]=r*cos(j*b);
			vt++;
		}
	}
	return str;
}

Cylindre * InitializeCylindre(Cylindre *str){

	int i,j;
	double a=2*PI/N;
  	double b=PI/P;/*double b=PI/P;*/
	/*double r=1;*/
	memset(str->vrtx, 20,N*P*sizeof(G3Xpoint));
	memset(str->norm, 20,N*P*sizeof(G3Xvector));
	G3Xpoint *vt=str->vrtx;
	for(i=0;i<N;i++)
	{

		for (j=0;j<P;j++)
		{
			(*vt)[0]=r*cos(i*a);
			(*vt)[1]=r*sin(i*a);
			(*vt)[2]=j*b;

			vt++;
		}
	}
	return str;
}


Pave * InitializePave(Pave *str){

	int i,j;
	double a=2*PI/N;
  	double b=2*PI/P;/*double b=PI/P;*/
	/*double r=1;*/
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

void DrawPave(Pave * str){

	int i,j,k,N2,P2;
	i=0;
	j=0;
	k=0;
	int n=100;
	int p=100; 
	int stepn=N/n; int stepp=P/p;

	/*SQUELETTE PAVE*/
	glBegin(GL_POINTS);
	g3x_Material(bleu,ambi,diff,spec,shin,1.);

	for(i=0;i<3;i++){

		for(j=0;j<4;j++){
			glVertex3dv(str->vrtx[i*3+j]);
			glNormal3dv(str->vrtx[i*3+j]);
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

void DrawSphere(Sphere * str){

	int i,j,k,N2,P2;
	i=0;
	j=0;
	k=0;
	int n=100;
	int p=100; 
	int stepn=N/n; int stepp=P/p;

	/*SQUELETTE SPHERE*/
	glBegin(GL_POINTS);

	for(i=0;i<N;i+=stepn){

		for(j=0;j<P;j+=stepp){
			k=i*P+j;
			
			/*printf("\n %f %f %f !\n",str->vrtx[k][0],str->vrtx[k][1], str->vrtx[k][2]);*/

			glVertex3dv(str->vrtx[k]);
			glNormal3dv(str->norm[k]);

		}

	}
	glEnd();

	/*TEXTURE SPHERE*/
	glBegin(GL_QUADS);

	for(i=0;i<N;i+=stepn){
		for(j=0;j<P;j+=stepp){
			glVertex3dv(str->vrtx[i*N+j]);
			glVertex3dv(str->vrtx[i*N+j+10]);
			glVertex3dv(str->vrtx[(i+10)*N+j+10]);
			glVertex3dv(str->vrtx[(i+10)*N+j]);

		}


	}
	glEnd();

}


void DrawTore(Ressort * str){

	int i,j,k,N2,P2;
	i=0;
	j=0;
	k=0;
	int n=100;
	int p=100; 
	int stepn=N/n; int stepp=P/p;

	/*SQUELETTE TORE*/
	glBegin(GL_POINTS);

	for(i=0;i<N;i+=stepn){

		for(j=0;j<P;j+=stepp){
			k=i*P+j;
			
			/*printf("\n %f %f %f !\n",str->vrtx[k][0],str->vrtx[k][1], str->vrtx[k][2]);*/

			glVertex3dv(str->vrtx[k]);
			glNormal3dv(str->norm[k]);

		}

	}
	glEnd();

	/*TEXTURE TORE*/
	glBegin(GL_QUADS);

	for(i=0;i<2*N-stepn;i+=stepn){
		for(j=0;j<P;j+=stepp){
			glVertex3dv(str->vrtx[i*N+j]);
			glVertex3dv(str->vrtx[i*N+j+10]);
			glVertex3dv(str->vrtx[(i+10)*N+j+10]);
			glVertex3dv(str->vrtx[(i+10)*N+j]);

		}
	}
	glEnd();

}

void DrawCylindre(Cylindre * str){

	int i,j,k,N2,P2;
	i=0;
	j=0;
	k=0;
	int n=100;
	int p=100; 
	int stepn=N/n; int stepp=P/p;

	/*SQUELETTE TORE*/
	glBegin(GL_POINTS);

	for(i=0;i<N;i+=stepn){

		for(j=0;j<P;j+=stepp){
			k=i*P+j;
			
			/*printf("\n %f %f %f !\n",str->vrtx[k][0],str->vrtx[k][1], str->vrtx[k][2]);*/

			glVertex3dv(str->vrtx[k]);
			glNormal3dv(str->norm[k]);

		}

	}
	glEnd();

	/*TEXTURE TORE*/
	glBegin(GL_QUADS);

	for(i=0;i<N;i+=stepn){
		for(j=0;j<P;j+=stepp){
			glVertex3dv(str->vrtx[i*N+j]);
			glVertex3dv(str->vrtx[i*N+j+10]);
			glVertex3dv(str->vrtx[(i+10)*N+j+10]);
			glVertex3dv(str->vrtx[(i+10)*N+j]);

		}
	}
	glEnd();

}


Ressort r1;
static Ressort *ptr_r1=&r1;

Sphere s1;
static Sphere *ptr_s1=&s1;

Pave p1;
static Pave *ptr_p1=&p1;

Cylindre c1;
static Cylindre *ptr_c1=&c1;


void Init(void){
	memset(vrtx, 0,2*N*P*sizeof(G3Xpoint));
	memset(norm, 0,2*N*P*sizeof(G3Xvector));
	memset(vrtx2, 0,4*3*sizeof(G3Xvector));
	memset(norm2, 0,4*3*sizeof(G3Xvector));
	double a=2*PI/N;
  	double b=2*PI/P;/*double b=PI/P;*/
	double c=2*PI/P;
	int i,j,t;
	G3Xpoint *v=vrtx;
	G3Xpoint *v2=vrtx2;
	
	InitializeRessort(ptr_r1);
	InitializePave(ptr_p1);
	InitializeSphere(ptr_s1);
	InitializeCylindre(ptr_c1);


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

	glPushMatrix();
	glScalef(0.3,.3,0.3);
	glTranslatef(0.,0.,-10);
	glRotatef(10.,-110.,0.,0.);
	g3x_Material(rouge,ambi,diff,spec,shin,1.);
	int stepn=N/n, stepp=P/p;
	int i,j;
	/*glDisable(GL_LIGHTING);*/
	glPointSize(r);
	glColor4fv(rouge);
	/*glEnable(GL_LIGHTING);*/
	int k;


	glColor4fv(orange);
	g3x_Material(orange,ambi,diff,spec,shin,1.);


	glTranslatef(0.,-5.,-1);
	/* On dessine le Tore*/
	DrawTore(ptr_r1);


	glPopMatrix();
	glPushMatrix();
	glTranslatef(3.,0.,-1);
	DrawSphere(ptr_s1);

	glPopMatrix();
	glPushMatrix();
	glTranslatef(-3.,0.,-1);
	DrawPave(ptr_p1);

	glPopMatrix();
	glPushMatrix();
	glTranslatef(5.,0.,-1);
	DrawCylindre(ptr_c1);



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
	g3x_SetLightAmbient (1.,1.,1.);
	g3x_SetLightDiffuse (1.,1.,1.);
	g3x_SetLightSpecular(1.,1.,1.);

  /* fixe la position et la direction du spot lumineux */
	/* (c'est les valeurs par defaut)                    */	
	g3x_SetLightPosition (10.,10.,10.);
	g3x_SetLightDirection( 0., 0., 0.);  


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
