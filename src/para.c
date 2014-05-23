

double f(double input){

	double output=0;
	/*printf("%lf\n",input );*/
	if(input<1/2.0){
		output=0.5;		
	}
	else{
		output=1-input;

	}

	return output;
}

Shape * InitializePara(Shape * str){
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

		(*v2)[0]=i*a;
		(*v2)[1]=-1;
		(*v2)[2]=-0.5;
		v2++;

		(*v2)[0]=i*a;
		(*v2)[1]=1;
		(*v2)[2]=-0.5;
		v2++;


		(*v2)[0]=i*a;
		(*v2)[1]=0.5;
		(*v2)[2]=f(i*a);
		v2++;

		(*v2)[0]=i*a;
		(*v2)[1]=-0.5;
		(*v2)[2]=f(i*a);
		v2++;

		


	/*NORMALES */

	/*(*vn)[0]=0;
	(*vn)[1]=0;
	(*vn)[2]=T;
	vn++;*/

}

return str;
}


void DrawPara(Shape * str){

	int i,j,k,N2,P2,l;
	i=0;
	j=0;
	k=0;
	/*
	if(animate==true){
	InitializeParaTransformation(str,R);	
	}
	*/

	int stepn=N/n; int stepp=P/p;

	/*SQUELETTE PAVE*/
	glBegin(GL_POINTS);
	g3x_Material(bleu,ambi,diff,spec,shin,1.);

	for(i=0;i<str->pointNo;i++){

		glVertex3dv(str->vrtx[i]);
		
	}
	
	glEnd();

/*TEXTURE PAVE*/
	glEnable(GL_LIGHTING);
	glBegin(GL_QUADS);


	g3x_Material(bleu,ambi,diff,spec,shin,1.);

	for(i=0;i<str->pointNo-7;i++){

/*faces de coté ouvert*/
		glVertex3dv(str->vrtx[i]);
		glVertex3dv(str->vrtx[i+3]);
		glVertex3dv(str->vrtx[i+7]);
		glVertex3dv(str->vrtx[i+4]);
		

		glNormal3dv(str->norm[i]);

	}

	/*g3x_Material(rouge,ambi,diff,spec,shin,1.);*/

	

	glEnd(); 
	glDisable(GL_LIGHTING);

}
