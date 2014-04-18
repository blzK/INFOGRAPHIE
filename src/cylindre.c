
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
			glVertex3dv(str->vrtx[k]);
*/

	}

		glColor4fv(rouge);
		g3x_Material(vert,ambi,diff,spec,shin,1.);
		i=0;


		glEnd();

	}