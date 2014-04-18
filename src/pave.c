
Shape * InitializePave(Shape * str){

	int i,j;
	double a=2*PI/N;
	double b=2*PI/P;

	str->vrtx=malloc(8*sizeof(G3Xpoint));
	str->norm=malloc(6*sizeof(G3Xvector));
	memset(str->vrtx, 0,8*sizeof(G3Xpoint));
	memset(str->norm, 0,6*sizeof(G3Xvector));

	G3Xpoint *v2=str->vrtx;
	G3Xpoint *vn=str->norm;


/*PAVE*/

	(*v2)[0]=(-1)*T/(2.0f);
	(*v2)[1]=(-1)*T/(2.0f);
	(*v2)[2]=0;
	v2++;

	(*v2)[0]=T/2.0f;
	(*v2)[1]=-T/2.0f;
	(*v2)[2]=0;
	v2++;

	(*v2)[0]=T/2.0f;
	(*v2)[1]=T/2.0f;
	(*v2)[2]=0;
	v2++;



	(*v2)[0]=-T/2.0f;
	(*v2)[1]=T/2.0f;
	(*v2)[2]=0;
	v2++;
	


	(*v2)[0]=-T/2.0f;
	(*v2)[1]=-T/2.0f;
	(*v2)[2]=-T/2.0f;
	v2++;

	(*v2)[0]=T/2.0f;
	(*v2)[1]=-T/2.0f;
	(*v2)[2]=-T/2.0f;
	v2++;

	(*v2)[0]=T/2.0f;
	(*v2)[1]=T/2.0f;
	(*v2)[2]=-T/2.0f;
	v2++;

	(*v2)[0]=-T/2.0f;
	(*v2)[1]=T/2.0f;
	(*v2)[2]=-T/2.0f;


	(*vn)[0]=-T;
	(*vn)[1]=0;
	(*vn)[2]=0;
	vn++;

	(*vn)[0]=0;
	(*vn)[1]=T;
	(*vn)[2]=0;
	vn++;

	(*vn)[0]=T;
	(*vn)[1]=0;
	(*vn)[2]=0;
	vn++;
	
	(*vn)[0]=0;
	(*vn)[1]=-T;
	(*vn)[2]=0;
	vn++;


	(*vn)[0]=0;
	(*vn)[1]=0;
	(*vn)[2]=T;
	vn++;


	(*vn)[0]=0;
	(*vn)[1]=0;
	(*vn)[2]=-T;
	


	return str;
}

void DrawPave(Shape * str){

	int i,j,k,N2,P2,l;
	i=0;
	j=0;
	k=0;


	int stepn=N/n; int stepp=P/p;

	/*SQUELETTE PAVE*/
	glBegin(GL_POINTS);
	g3x_Material(bleu,ambi,diff,spec,shin,1.);

	for(i=0;i<8;i++){

		glVertex3dv(str->vrtx[i]);

		
	}
	
	glEnd();

/*TEXTURE PAVE*/

	glBegin(GL_QUADS);


	g3x_Material(bleu,ambi,diff,spec,shin,1.);

	for(i=0;i<3;i++){

/*faces de coté ouvert*/
		glVertex3dv(str->vrtx[i]);
		glVertex3dv(str->vrtx[i+1]);
		glVertex3dv(str->vrtx[i+5]);
		glVertex3dv(str->vrtx[i+4]);

		glNormal3dv(str->norm[i]);

	}

	/*g3x_Material(rouge,ambi,diff,spec,shin,1.);*/

	




/*on ferme le coté */

	glVertex3dv(str->vrtx[0]);
	glVertex3dv(str->vrtx[3]);
	glVertex3dv(str->vrtx[7]);
	glVertex3dv(str->vrtx[4]);
	glNormal3dv(str->norm[3]);
	g3x_Material(orange,ambi,diff,spec,shin,1.);

/*faces du dessus*/

	glVertex3dv(str->vrtx[0]);
	glVertex3dv(str->vrtx[1]);
	glVertex3dv(str->vrtx[2]);
	glVertex3dv(str->vrtx[3]);
	glNormal3dv(str->norm[4]);
/*face d'en bas*/

	glVertex3dv(str->vrtx[4]);
	glVertex3dv(str->vrtx[5]);
	glVertex3dv(str->vrtx[6]);
	glVertex3dv(str->vrtx[7]);
	glNormal3dv(str->norm[5]);


	glEnd();

}