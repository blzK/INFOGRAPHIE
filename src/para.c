

double f(double input){

	double output=0;
	/*printf("%lf\n",input );*/
	if(input<0.8){
		output=0.5;		
	}
	else{
		output=2.5-2.5*input;

	}

	return output;
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


/*PAVE*/


	for(i=0;i<N;i++)
	{

		(*v2)[0]=i*a-0,5;
		(*v2)[1]=-0.5;
		(*v2)[2]=-0.5;
		v2++;

		(*v2)[0]=i*a;
		(*v2)[1]=0.5;
		(*v2)[2]=-0.5;
		v2++;


		(*v2)[0]=i*a-0,5;
		(*v2)[1]=0.25;
		(*v2)[2]=f(i*a);
		v2++;

		(*v2)[0]=i*a;
		(*v2)[1]=-0.25;
		(*v2)[2]=f(i*a);
		v2++;

		


	/*NORMALES */

	/*(*vn)[0]=0;
	(*vn)[1]=0;
	(*vn)[2]=T;
	vn++;*/

}

}

void calculateNorm(Shape * str){

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


/*PAVE*/


	for(i=0;i<N;i++)
	{

		(*v2)[0];
		(*v2)[1];
		(*v2)[2];
		v2++;

		(*v2)[0];
		(*v2)[1];
		(*v2)[2];
		v2++;


		(*v2)[0]=;
		(*v2)[1]=;
		(*v2)[2]=;
		v2++;

		(*v2)[0];
		(*v2)[1];
		(*v2)[2];
		v2++;

	/*NORMALES */

	/*(*vn)[0]=0;
	(*vn)[1]=0;
	(*vn)[2]=T;
	vn++;*/


}

void DrawPara(Shape * str){

	int i,j,k,l;
	i=0;
	j=0;
	k=0;

	int stepn=N/n; 
	int stepp=P/p;

	/*SQUELETTE PAVE*/
	glBegin(GL_POINTS);

	for(i=0;i<4*N;i++){

		glVertex3dv(str->vrtx[i]);
		
	}
	
	glEnd();

/*TEXTURE PAVE*/
	glEnable(GL_LIGHTING);
	glBegin(GL_QUADS);


	i=4;
	glVertex3dv(str->vrtx[i]);
	glVertex3dv(str->vrtx[i+1]);
	glVertex3dv(str->vrtx[i+2]);
	glVertex3dv(str->vrtx[i+3]);

	for(i=0;i<4*N-7;i++){

/*faces de coté ouvert*/
		glVertex3dv(str->vrtx[i]);
		glVertex3dv(str->vrtx[i+3]);
		glVertex3dv(str->vrtx[i+7]);
		glVertex3dv(str->vrtx[i+4]);
		

		glNormal3dv(str->norm[i]);

	}

	glVertex3dv(str->vrtx[i]);
	glVertex3dv(str->vrtx[i+1]);
	glVertex3dv(str->vrtx[i+2]);
	glVertex3dv(str->vrtx[i+3]);


	glEnd(); 
	glDisable(GL_LIGHTING);

}
