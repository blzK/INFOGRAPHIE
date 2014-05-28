Shape * InitializeGauss(Shape * str){
	int i,j;
	int offset=3.;
	double a=6./N;
	double b=6./N;

	str->pointNo=N*P;
	str->normNo=N*P;
	str->vrtx=malloc(P*N*sizeof(G3Xpoint));
	str->norm=malloc(P*N*sizeof(G3Xvector));
	memset(str->vrtx, 0,N*sizeof(G3Xpoint));
	memset(str->norm, 0,N*sizeof(G3Xvector));

	G3Xpoint *vt=str->vrtx;
	G3Xpoint *vn=str->norm;


	for(i=0;i<N;i++)
	{

		for (j=0;j<P;j++)
		{
			(*vt)[0]=i*a-offset;
			(*vt)[1]=j*b-offset;
			(*vt)[2]=2*exp(-(i*a-offset)*(i*a-offset))*exp(-(j*b-offset)*(j*b-offset));
			vt++;

			(*vn)[0]=i*a;
			(*vn)[1]=j*a;
			(*vn)[2]=2*exp(-i*a)*exp(-j*b);
			vn++;

		}

	}

	return str;
}


void DrawGauss(Shape * str){

	int i,j,k,N2,P2,l;
	i=0;
	j=0;
	k=0;
/*
if(animate==true){
InitializeGaussTransformation(str,R);	
}
*/

int stepn=N/n; int stepp=P/p;

/*SQUELETTE PAVE*/
/*glBegin(GL_POINTS);
g3x_Material(bleu,ambi,diff,spec,shin,1.);

for(i=0;i<N*P;i++){

	glVertex3dv(str->vrtx[i]);

}

glEnd();
*/
/*TEXTURE PAVE*/
glEnable(GL_LIGHTING);
glBegin(GL_QUADS);

/*
for(i=0;i<str->pointNo;i++){

/*faces de coté ouvert*/
	/*glVertex3dv(str->vrtx[i]);

	glNormal3dv(str->norm[i]);

}


/*g3x_Material(rouge,ambi,diff,spec,shin,1.);*/

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
}

glEnd(); 
glDisable(GL_LIGHTING);

}
