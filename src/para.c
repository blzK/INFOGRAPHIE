

double f(double input){

	double output=0;
	/*printf("%lf\n",input );*/
	if(input<=0.8){
		output=0.5;		
	}
	else{
		output=2.5-2.5*input;

	}

	return output;
}




void calculateNormPara(Shape * str){

	int i,j;
	double a=1.0/N;
	str->norm=malloc(N*sizeof(G3Xvector));
	memset(str->norm, 0,N*sizeof(G3Xvector));

	G3Xpoint *v2=str->vrtx;
	G3Xpoint *vn=str->norm;
	/*G3Xpoint *ptemp;
	ptemp=malloc(3*sizeof(G3Xpoint));
*/
	G3Xpoint ptemp[3];

/*PAVE*/


	for(i=0;i<N;i++)
	{



		(ptemp[0])[0]=(v2[i])[0];
		(ptemp[0])[1]=(v2[i])[1];
		(ptemp[0])[2]=(v2[i])[2];

		(ptemp[1])[0]=(v2[i+3])[0];
		(ptemp[1])[1]=(v2[i+3])[1];
		(ptemp[1])[2]=(v2[i+3])[2];

		/*(ptemp[2])[0]=(v2[i+7])[0];
		(ptemp[2])[1]=(v2[i+7])[1];
		(ptemp[2])[2]=(v2[+7])[2];*/

		/**! ATTENTION AU SENS DIRECT !**/
		G3Xmid(ptemp[2],v2[i+3],v2[i+7]);
		G3Xprodvect3point((*vn),ptemp[0],ptemp[1],ptemp[2]);
		vn++;

		printf("%lf,%lf,%lf\n", (ptemp[0])[0],(ptemp[0])[1],(ptemp)[0][2]);
		printf("%lf,%lf,%lf\n", (ptemp[1])[0],(ptemp[1])[1],(ptemp)[1][2]);
		printf("%lf,%lf,%lf\n", (ptemp[2])[0],(ptemp[2])[1],(ptemp)[2][2]);
		printf("********\n");
		printf("%lf,%lf,%lf\n", (*vn)[0],(*vn)[1],(*vn)[2]);
		printf("********\n");

/*On a pas besoin du quatrième point*/


	}
}
void * InitializePara(Shape * str){
	int i,j;
	double a=1.0/N;
	str->pointNo=4*N;
	str->normNo=N;
	str->vrtx=malloc(4*N*sizeof(G3Xpoint));
	str->norm=malloc(N*sizeof(G3Xvector));
	memset(str->vrtx, 0,N*sizeof(G3Xpoint));
	memset(str->norm, 0,N*sizeof(G3Xvector));

	G3Xpoint *v2=str->vrtx;
	G3Xpoint *vn=str->norm;

	G3Xpoint ptemp[3];
	/*ptemp=malloc(3*sizeof(G3Xpoint));*/

/*PAVE*/




	for(i=0;i<N;i++)
	{

		(*v2)[0]=i*a-0,5;
		(*v2)[1]=-0.5;
		(*v2)[2]=-0.5;
		/*(ptemp[0])[0]=(*v2)[0];
		(ptemp[0])[1]=(*v2)[1];
		(ptemp[0])[2]=(*v2)[2];*/
		v2++;

		(*v2)[0]=i*a;
		(*v2)[1]=0.5;
		(*v2)[2]=-0.5;
		/*(ptemp[1])[0]=(*v2)[0];
		(ptemp[1])[1]=(*v2)[1];
		(ptemp[1])[2]=(*v2)[2];*/
		v2++;


		(*v2)[0]=i*a-0,5;
		(*v2)[1]=0.25;
		(*v2)[2]=f(i*a);
		/*(ptemp[2])[0]=(*v2)[0];
		(ptemp[2])[1]=(*v2)[1];
		(ptemp[2])[2]=(*v2)[2];*/
		v2++;

		(*v2)[0]=i*a;
		(*v2)[1]=-0.25;
		(*v2)[2]=f(i*a);
		v2++;


		/*G3Xprodvect3point((*vn),ptemp[0],ptemp[1],ptemp[2]);
		printf("%lf,%lf,%lf\n", (ptemp[0])[0],(ptemp[0])[1],(ptemp)[0][2]);
		printf("%lf,%lf,%lf\n", (ptemp[1])[0],(ptemp[1])[1],(ptemp)[1][2]);
		printf("%lf,%lf,%lf\n", (ptemp[2])[0],(ptemp[2])[1],(ptemp)[2][2]);
		printf("********\n");
		printf("%lf,%lf,%lf\n", (*vn)[0],(*vn)[1],(*vn)[2]);
		printf("********\n");
		/*ptemp=ptemp-2;*/
		/*vn++;


	/*NORMALES */

	/*(*vn)[0]=0;
	(*vn)[1]=0;
	(*vn)[2]=T;
	vn++;*/

}
calculateNormPara(str);

}


void DrawPara(Shape * str){
	int i,j,k,l;
	i=0;
	j=0;
	k=0;

	int stepn=N/n; 
	int stepp=P/p;

	/*SQUELETTE PAVE*/
/*	glBegin(GL_POINTS);

	for(i=0;i<4*N;i++){

		glVertex3dv(str->vrtx[i]);
		
	}
	
	glEnd();

/*TEXTURE PAVE*/
	glEnable(GL_LIGHTING);
	glBegin(GL_QUADS);


	i=4;
	glNormal3dv(str->norm[i]);
	glVertex3dv(str->vrtx[i]);
	glVertex3dv(str->vrtx[i+1]);
	glVertex3dv(str->vrtx[i+2]);
	glVertex3dv(str->vrtx[i+3]);
	

	for(i=0;i<4*N-7;i++){

		glNormal3dv(str->norm[i]);
/*faces de coté ouvert*/
		glVertex3dv(str->vrtx[i]);
		glVertex3dv(str->vrtx[i+3]);
		glVertex3dv(str->vrtx[i+7]);
		glVertex3dv(str->vrtx[i+4]);
		


	}
	glNormal3dv(str->norm[i]);
	glVertex3dv(str->vrtx[i]);
	glVertex3dv(str->vrtx[i+1]);
	glVertex3dv(str->vrtx[i+2]);
	glVertex3dv(str->vrtx[i+3]);
	


	/*for(i=0;i<N;i++)
	{
		glNormal3dv(str->norm[i]);
	}*/
		glEnd(); 
		glDisable(GL_LIGHTING);


	}
