

Shape * InitializeCylindre(Shape * str){
	int i,j;
	double a=2*PI/N;
	double b=PI/P;
	double rayon=0.5;
	str->pointNo=N*P;
	str->normNo=N*P;
	str->vrtx=malloc(N*P*sizeof(G3Xpoint));
	str->norm=malloc(N*P*sizeof(G3Xvector));
	memset(str->vrtx, 0,N*P*sizeof(G3Xpoint));
	memset(str->norm, 0,N*P*sizeof(G3Xvector));
	G3Xpoint *vt=str->vrtx;  
	G3Xvector *vn=str->norm;

	for(i=0;i<N;i++)
	{

		for (j=0;j<P;j++)
		{

			(*vt)[0]=rayon*cos(i*a);
			(*vt)[1]=rayon*sin(i*a);
			(*vt)[2]=2*j*rayon/P-0.5;	

			(*vn)[0]=cos(i*a);
			(*vn)[1]=sin(i*a);
			(*vn)[2]=0;

			vn++;
			vt++;
		}

	}

	return str;
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
	glPointSize(0); 
	glDisable(GL_LIGHTING);
/*	glBegin(GL_POINTS);
	glPointSize(0); 
	for(i=0;i<N-stepn;i+=stepn){

		for(j=0;j<P-stepp;j+=stepp){
			k=i*N+j;

			/*printf("\n %f %f %f !\n",str->vrtx[k][0],str->vrtx[k][1], str->vrtx[k][2]);*/

	/*		glVertex3dv(str->vrtx[k]);
			glNormal3dv(str->norm[k]);

		}

	}
	glEnd();

	/*TEXTURE CYLINDRE*/
	glEnable(GL_LIGHTING);
	glBegin(GL_QUADS);
	
	

	for(i=0;i<N-stepn;i+=stepn){
		for(j=0;j<P-stepp;j+=stepp){

			k = i*P+j;
			glVertex3dv(str->vrtx[k]);
			glNormal3dv(str->norm[k]);

			k = i*P + (j+stepp);
			glVertex3dv(str->vrtx[k]);
			glNormal3dv(str->norm[k]);

			k = (i+stepn)*P+(j+stepp);
			glVertex3dv(str->vrtx[k]);
			glNormal3dv(str->norm[k]);


			k = (i+stepn)*P + j; 
			glVertex3dv(str->vrtx[k]);
			glNormal3dv(str->norm[k]);
			

		}

	}
	

	
/*raccordement */

	i=N-stepn;
	j=P-stepp;
	k = i*P+j;
	glNormal3dv(str->norm[k]);
	glVertex3dv(str->vrtx[k]);

	j=0;
	i=N-stepn;
	k = i*P+j;
	glNormal3dv(str->norm[k]);
	glVertex3dv(str->vrtx[k]);

	j=0;
	i=0;
	k = i*P+j;
	glNormal3dv(str->norm[k]);
	glVertex3dv(str->vrtx[k]);

	j=P-stepp;
	i=0;
	k = i*P+j;
	glNormal3dv(str->norm[k]);
	glVertex3dv(str->vrtx[k]);

	
	

	glEnd();


	/*g3x_Material(rouge,ambi,diff,spec,shin,1.);*/
	/* Socle : cercle pour le bas du cylindre */

	glEnable(GL_LIGHTING);
	glBegin(GL_POLYGON);
	
	for(i = 0; i < N-stepn; i+= stepn)
	{
		/*i*p+j*/
		i=i%N;
		j=P-stepp;
		k=i*P+j;
		k = i*P + j;
		glNormal3dv(str->norm[k]);
		glVertex3dv(str->vrtx[k]);
	}
	glNormal3dv(str->norm[(N - stepn)*P + j%P]);
	glVertex3dv(str->vrtx[(N - stepn)*P + j%P]);
	
	glEnd();


/* Couvercle : cercle pour le haut du cylindre */
	/*glBegin(GL_POLYGON);
	for(j = 0; j < P-stepp; j+= stepp)
	{
		k = (N/2 - stepn)*P + j%P;
		glNormal3dv(str->norm[k]);
		glVertex3dv(str->vrtx[k]);
	}
	glNormal3dv(str->norm[(N/2 - stepn)*P + j%P]);
	glVertex3dv(str->vrtx[(N/2 - stepn)*P + j%P]);
	glEnd();
	glEnable(GL_LIGHTING);*/


}






	/*************/
/*
glDisable(GL_LIGHTING);
g3x_Material(color, ambi, diff, spec, shine, alpha);
glBegin(GL_QUADS);
for( i = 0; i < N - stepn; i+= stepn)
{
for(j = 0; j < P-stepp; j+= stepp)
{
k = i*P+j;
glNormal3dv(cylindre_normale[k]);
glVertex3dv(cylindre_vertex[k]);

k = i*P + (j+stepp);
glNormal3dv(cylindre_normale[k]);
glVertex3dv(cylindre_vertex[k]);

k = (i+stepn)*P+(j+stepp);
glNormal3dv(cylindre_normale[k]);
glVertex3dv(cylindre_vertex[k]);

k = (i+stepn)*P + j;
glNormal3dv(cylindre_normale[k]);
glVertex3dv(cylindre_vertex[k]);

}
k = i*P+j;
glNormal3dv(cylindre_normale[k]);
glVertex3dv(cylindre_vertex[k]);

k = i*P;
glNormal3dv(cylindre_normale[k]);
glVertex3dv(cylindre_vertex[k]);

k = (i+stepn)*P;
glNormal3dv(cylindre_normale[k]);
glVertex3dv(cylindre_vertex[k]);

k = (i+stepn)*P + j;
glNormal3dv(cylindre_normale[k]);
glVertex3dv(cylindre_normale[k]);
}
glEnd();

/* Socle : cercle pour le bas du cylindre */
/*glBegin(GL_POLYGON);
for(j = 0; j < P-stepp; j+= stepp)
{
k = (N - stepn)*P + j%P;
glNormal3dv(cylindre_normale[k]);
glVertex3dv(cylindre_normale[k]);
}
glNormal3dv(cylindre_normale[(N - stepn)*P + j%P]);
glVertex3dv(cylindre_normale[(N - stepn)*P + j%P]);
glEnd();


/* Couvercle : cercle pour le haut du cylindre */
/*glBegin(GL_POLYGON);
for(j = 0; j < P-stepp; j+= stepp)
{
k = (N/2 - stepn)*P + j%P;
glNormal3dv(cylindre_normale[k]);
glVertex3dv(cylindre_normale[k]);
}
glNormal3dv(cylindre_normale[(N/2 - stepn)*P + j%P]);
glVertex3dv(cylindre_normale[(N/2 - stepn)*P + j%P]);
glEnd();
glEnable(GL_LIGHTING);
}*/
