

Shape * InitializePave(Shape * str){

	int i,j;
	double a=2*PI/N;
	double b=2*PI/P;
	str->pointNo=8;
	str->normNo=6;
	str->vrtx=malloc(8*sizeof(G3Xpoint));
	str->norm=malloc(6*sizeof(G3Xvector));
	memset(str->vrtx, 0,8*sizeof(G3Xpoint));
	memset(str->norm, 0,6*sizeof(G3Xvector));

	G3Xpoint *v2=str->vrtx;
	G3Xpoint *vn=str->norm;


/*PAVE*/

	(*v2)[0]=(-1)*T/(2.0f);
	(*v2)[1]=(-1)*T/(2.0f);
	(*v2)[2]=T/2.0f;
	v2++;

	(*v2)[0]=T/2.0f;
	(*v2)[1]=-T/2.0f;
	(*v2)[2]=T/2.0f;
	v2++;

	(*v2)[0]=T/2.0f;
	(*v2)[1]=T/2.0f;
	(*v2)[2]=T/2.0f;
	v2++;



	(*v2)[0]=-T/2.0f;
	(*v2)[1]=T/2.0f;
	(*v2)[2]=T/2.0f;
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

/*NORMALES */
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
	/*
	if(animate==true){
	InitializePaveTransformation(str,R);	
	}
	*/

	int stepn=N/n; int stepp=P/p;

	/*SQUELETTE PAVE*/
/*	glBegin(GL_POINTS);

	for(i=0;i<8;i++){

		glVertex3dv(str->vrtx[i]);

		
	}
	
	glEnd();
*/
/*TEXTURE PAVE*/
	glEnable(GL_LIGHTING);
	glBegin(GL_QUADS);



	for(i=0;i<3;i++){

/*faces de coté ouvert*/
		glNormal3dv(str->norm[i]);
		glVertex3dv(str->vrtx[i]);
		glNormal3dv(str->norm[i]);
		glVertex3dv(str->vrtx[i+1]);
		glNormal3dv(str->norm[i]);
		glVertex3dv(str->vrtx[i+5]);
		glNormal3dv(str->norm[i]);
		glVertex3dv(str->vrtx[i+4]);

		

	}

	/*g3x_Material(rouge,ambi,diff,spec,shin,1.);*/

	




/*on ferme le coté */
glNormal3dv(str->norm[3]);
	glVertex3dv(str->vrtx[0]);
	glNormal3dv(str->norm[3]);
	glVertex3dv(str->vrtx[3]);
	glNormal3dv(str->norm[3]);
	glVertex3dv(str->vrtx[7]);
	glNormal3dv(str->norm[3]);
	glVertex3dv(str->vrtx[4]);
	

/*faces du dessus*/
glNormal3dv(str->norm[4]);
	glVertex3dv(str->vrtx[0]);
	glNormal3dv(str->norm[4]);
	glVertex3dv(str->vrtx[1]);
	glNormal3dv(str->norm[4]);
	glVertex3dv(str->vrtx[2]);
	glNormal3dv(str->norm[4]);
	glVertex3dv(str->vrtx[3]);
	
	
/*face d'en bas*/
glNormal3dv(str->norm[5]);
	glVertex3dv(str->vrtx[4]);
	glNormal3dv(str->norm[5]);
	glVertex3dv(str->vrtx[5]);
	glNormal3dv(str->norm[5]);
	glVertex3dv(str->vrtx[6]);
	glNormal3dv(str->norm[5]);
	glVertex3dv(str->vrtx[7]);
	


	glEnd();

}
