void CalculateNormals(Shape * str){
	int i;
	for (i = 0; i < str->pointNo; ++i)
	{
		if(i%4==0){
			G3Xprodvect3point(str->norm[i],str->vrtx[i],str->vrtx[i+1],str->vrtx[i+2]);
		}
	}

}
Shape * InitializeTore(Shape *str, double ratio){

	int i,j;
	double a=2*PI/N;
  	double b=2*PI/P;/*double b=PI/P;*/
	double rayon=0.5;

	str->ratio=ratio;
	str->pointNo=N*P;
	str->normNo=(int)N*P/3.;
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
			(*vt)[0]=(rayon+str->ratio*rayon*cos(j*a))*(cos(i*b));
			(*vt)[1]=(rayon+str->ratio*rayon*cos(j*a))*sin(i*b);
			(*vt)[2]=rayon*sin(j*a);

			ptemp[i%4]=vt;


			vt++;
		}
	}

	CalculateNormals(str);
	return str;


}


		/*	if(i%3==0){
				/*printf("%d %d %d \n", ptemp[0][0],ptemp[1][1],ptemp[2][1]);*/
				/**/
/*G3Xprodvect3point((*vn),ptemp[0],ptemp[1],ptemp[2]);

		/*		vn++;
			}
			*/



			void DrawTore(Shape * str){

				int i,j,k;
				i=0;
				j=0;
				k=0;

				int stepn=N/n; int stepp=P/p;

	/*SQUELETTE TORE*/
				glBegin(GL_POINTS);
				glDisable(GL_LIGHTING);

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
				glEnable(GL_LIGHTING);
				for(i=0;i<N-stepn;i+=stepn){
					for(j=0;j<P-stepp;j+=stepp){


			/*glVertex3dv(str->vrtx[i*N+j]);
			glVertex3dv(str->vrtx[i*N+j+stepp]);
			glVertex3dv(str->vrtx[(i+stepn)*N+j+stepp]);
			glVertex3dv(str->vrtx[(i+stepn)*N+j]);

*/

			k = i*P+j;
			/*glNormal3dv(str->norm[k]);*/
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

			

			/*glNormal3dv(str->norm[(i*P+j)]);*/

			

		}


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
	glDisable(GL_LIGHTING);
	glEnd();
	/*Raccordement*/

	/*glColor4fv(rouge);*/
/*	g3x_Material(rouge,ambi,diff,spec,shin,1.);*/
	glBegin(GL_POLYGON);

	for(j=0;j<P;j+=stepp){
	/*	glVertex3dv(str->vrtx[N*P+j]);
		glVertex3dv(str->vrtx[N*P+j+stepp]);
		glVertex3dv(str->vrtx[(stepn)*N+j+stepp]);
		glVertex3dv(str->vrtx[(stepn)*N+j]);
*/
		i=stepn;
		k = i*P+j;
		glVertex3dv(str->vrtx[k]);

		k = i*P+j+stepp;
		glVertex3dv(str->vrtx[k]);

		i=N-stepn;
		k = i*P+j;
		glVertex3dv(str->vrtx[k]);

		k = i*P+j+stepp;
		glVertex3dv(str->vrtx[k]);




		
		


	}

	glDisable(GL_LIGHTING);
	glEnd();
}