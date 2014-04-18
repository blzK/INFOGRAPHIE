
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