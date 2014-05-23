

Shape * InitializeRessort(Shape * str){

	int i,j;
	double a=2*PI/N;
  	double b=2*PI/P;/*double b=PI/P;*/
	double r=1;
	str->pointNo=2*N*P;
	str->normNo=2*N*P;
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
};


void DrawRessort(Shape * str, double *ptr_Mat){
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

};