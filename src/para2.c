void calculateNormGauss(Shape * str){
	int i,j;
	double a=1.0/N;
	str->norm=malloc(N*P*sizeof(G3Xvector));
	memset(str->norm, 0,N*P*sizeof(G3Xvector));

	G3Xpoint *v2=str->vrtx;
	G3Xpoint *vn=str->norm;
	/*G3Xpoint *ptemp;
	ptemp=malloc(3*sizeof(G3Xpoint));
*/
	G3Xpoint ptemp[3];

/*PAVE*/


	int stepn=N/n; int stepp=P/p; int k;
	for(i=0;i<N-stepn;i+=stepn){
		for(j=0;j<P-stepp;j+=stepp){

			k = i*P+j;
			(ptemp[0])[0]=(v2[k])[0];
			(ptemp[0])[1]=(v2[k])[1];
			(ptemp[0])[2]=(v2[k])[2];

			k = i*P + (j+stepp);
			(ptemp[1])[0]=(v2[k])[0];
			(ptemp[1])[1]=(v2[k])[1];
			(ptemp[1])[2]=(v2[k])[2];

			/*k = (i+stepn)*P+(j+stepp);

			(ptemp[2])[0]=(v2[k])[0];
			(ptemp[2])[1]=(v2[k])[1];
			(ptemp[2])[2]=(v2[k])[2];

			k = (i+stepn)*P + j; */

			G3Xmid(ptemp[2],v2[(i+stepn)*P+(j+stepp)],v2[(i+stepn)*P + j]);
			G3Xprodvect3point((*vn),ptemp[0],ptemp[1],ptemp[2]);

		}
	}

}


Shape * InitializeGauss(Shape * str){
	int i,j;
	int offset=3.;
	double a=6./N;
	double b=6./N;
	/*N=N*(str->detail);
	P=P*(str->detail);*/
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
	calculateNormGauss(str);
	N=N_default;
	P=P_default;
	return str;
}


void DrawGauss(Shape * str){
/*calculateNormGauss(str);*/
	N=N*(str->detail);
	P=P*(str->detail);
	int i,j,k,N2,P2,l,k2;
	i=0;
	j=0;
	k=0;

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


/*g3x_Material(rouge,ambi,diff,spec,shin,1.);*/

for(i=0;i<N-stepn;i+=stepn){
	for(j=0;j<P-stepp;j+=stepp){



		k = i*P+j;
		k2 = i*P+j;
		glNormal3dv(str->norm[k2]);
		glVertex3dv(str->vrtx[k]);

		k = i*P + (j+stepp);
		glNormal3dv(str->norm[k2]);
		glVertex3dv(str->vrtx[k]);

		k = (i+stepn)*P+(j+stepp);
		glNormal3dv(str->norm[k2]);
		glVertex3dv(str->vrtx[k]);

		k = (i+stepn)*P + j; 
		glNormal3dv(str->norm[k2]);
		glVertex3dv(str->vrtx[k]);

	}
}

glEnd(); 
glDisable(GL_LIGHTING);
N=N_default;
P=P_default;

}
