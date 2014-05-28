
Shape * InitializeSphere(Shape * str){

	int i,j;
	double a=2*PI/N;
	double b=PI/P;
	str->pointNo=N*P;
	str->normNo=N*P;

	str->vrtx=malloc(N*P*sizeof(G3Xpoint));
	str->norm=malloc(N*P*sizeof(G3Xvector));
	/*memset(str->vrtx, 0,N*P*sizeof(G3Xpoint));
	memset(str->norm, 0,N*P*sizeof(G3Xvector));*/
	G3Xvector *vn=str->norm;
	G3Xpoint *vt=str->vrtx;

	for(i=0;i<N;i++)
	{

		for (j=0;j<P;j++)
		{
			(*vt)[0]=cos(i*a)*sin(j*b);
			(*vt)[1]=sin(i*a)*sin(j*b);
			(*vt)[2]=cos(j*b);

/*normale sphere*/
			/*
			(*vn)[0]=r*cos(i*a);
			(*vn)[1]=r*sin(i*a);
			(*vn)[2]=r*cos(j*b);
*/

			(*vn)[0]=cos(i*a)*sin(j*b);
			(*vn)[1]=sin(i*a)*sin(j*b);
			(*vn)[2]=cos(j*b);

			vn++;
			vt++;
		}
	}
	return str;
}


void DrawSphere(Shape * str){


	str->pointNo=N*P;

	int i,j,k,N2,P2;
	i=0;
	j=0;
	k=0;

	int stepn=N/n; int stepp=P/p;

	/*SQUELETTE SPHERE*/
	/*glBegin(GL_POINTS);

	for(i=0;i<N-stepn;i+=stepn){

		for(j=0;j<P-stepp;j+=stepp){
			k=i*P+j;

			/*printf("\n %f %f %f !\n",str->vrtx[k][0],str->vrtx[k][1], str->vrtx[k][2]);*/

/*			glVertex3dv(str->vrtx[k]);
			

		}

	}
glEnd();*/ 

	/*TEXTURE SPHERE*/
	glBegin(GL_QUADS);

	for(i=0;i<N-stepn;i+=stepn){
		for(j=0;j<P-stepp;j+=stepp){

			k = i*P+j;
			glNormal3dv(str->norm[k]);
			glVertex3dv(str->vrtx[k]);

			k = i*P + (j+stepp);
			glNormal3dv(str->norm[k]);
			glVertex3dv(str->vrtx[k]);

			k = (i+stepn)*P+(j+stepp);
			glNormal3dv(str->norm[k]);
			glVertex3dv(str->vrtx[k]);

			k = (i+stepn)*P + j; 
			glNormal3dv(str->norm[k]);
			glVertex3dv(str->vrtx[k]);

		}
		/*k = i*P+j;
		glNormal3dv(str->norm[k]);
		glVertex3dv(str->vrtx[k]);

		k = i*P + (j+stepp);
		glNormal3dv(str->norm[k]);
		glVertex3dv(str->vrtx[k]);

		k = (i+stepn)*P+(j+stepp);
		glNormal3dv(str->norm[k]);
		glVertex3dv(str->vrtx[k]);

		k = (i+stepn)*P + j; 
		glNormal3dv(str->norm[k]);
		glVertex3dv(str->vrtx[k]);*/


	}

/*
glBegin(GL_POLYGON);

	for(j=0;j<P;j+=stepp){


		i=N-stepn;
		k = i+j;
		glNormal3dv(str->norm[k]);
		glVertex3dv(str->vrtx[k]);

		k = i + (j+stepp);
		glNormal3dv(str->norm[k]);
		glVertex3dv(str->vrtx[k]);

		i=0;
		k = (i+stepn)+(j+stepp);
		glNormal3dv(str->norm[k]);
		glVertex3dv(str->vrtx[k]);

		k = (i+stepn) + j; 
		glNormal3dv(str->norm[k]);
		glVertex3dv(str->vrtx[k]);

	}
*/

	/*glEnd();
	glBegin(GL_POLYGON);
*/
/*On raccommode */

	for(j=0;j<P-stepp;j+=stepp){
	/*	glVertex3dv(str->vrtx[N*P+j]);
		glVertex3dv(str->vrtx[N*P+j+stepp]);
		glVertex3dv(str->vrtx[(stepn)*N+j+stepp]);
		glVertex3dv(str->vrtx[(stepn)*N+j]);
*/
		i=0;
		k = i*P+j;
		glNormal3dv(str->norm[k]);
		glVertex3dv(str->vrtx[k]);
		

		k = i*P+j+stepp;
		glNormal3dv(str->norm[k]);
		glVertex3dv(str->vrtx[k]);
		

		i=N-stepn;


		k = i*P+j+stepp;
		glNormal3dv(str->norm[k]);
		glVertex3dv(str->vrtx[k]);

		k = i*P+j;
		glNormal3dv(str->norm[k]);
		glVertex3dv(str->vrtx[k]);
		
		


	}
	glEnd();

	/*On bouche le trou */

	glBegin(GL_POLYGON);
	j=P-stepp;
	for(i=0;i<N-stepn;i+=stepn){
		k = i*P+j;
		glNormal3dv(str->norm[k]);
		glVertex3dv(str->vrtx[k]);
	}

	glDisable(GL_LIGHTING);
	
	
	glEnd();
}

