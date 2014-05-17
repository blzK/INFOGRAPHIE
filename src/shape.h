#include <stdio.h>
#include <g3x.h>



typedef struct Shape
{
	G3Xpoint *vrtx;/*pointeurs vers les tableaux du vertex canonique*/
	G3Xvector *norm;/*pointeurs vers les tableaux du normales canonique*/
	G3Xcolor col; /*Couleur*/
  	int ID; /*type*/
	double ambi, diff, spec, shine, alpha; /*materiau*/
	int pointNo; /*Nombre de vertex*/
	bool initialized;
	int normNo; /*Nombre de normales*/
} Shape;


bool UpdateShape(Shape * str,  double *ptr_Mat){

	
	G3Xpoint *v2=str->vrtx;
	G3Xpoint *vn= str->norm;
	G3Xpoint *vC;
	G3Xpoint *vCn;

	int q;
	q=0;

	G3Xpoint ResultPoint;
	G3Xpoint ResultPoint2;
/*
Il faudrait faire la multiplication avec la forme canonique !
donc sauvegarder un type canonique...

*/
for (q = 0; q < str->pointNo; ++q){
	g3x_ProdHMatPoint(ptr_Mat, *v2, ResultPoint);
	(*v2)[0]=ResultPoint[0];
	(*v2)[1]=ResultPoint[1];
	(*v2)[2]=ResultPoint[2];
	v2++; 
}

/*
for (q = 0; q < str->normNo; ++q){
	g3x_ProdHMatPoint(ptr_Mat, *vCn, ResultPoint2);
		/*Transformation des normales*/
/*	(*vn)[0]=ResultPoint2[0];
	(*vn)[1]=ResultPoint2[1];
	(*vn)[2]=ResultPoint2[2];
	vCn++;  
	vn++;   

}

/*
for (q = 0; q < str->normNo; ++q){
	g3x_ProdHMatPoint(ptr_Mat, *vCn, ResultPoint2);
		/*Transformation des normales*/
/*	(*vn)[0]=ResultPoint2[0];
	(*vn)[1]=ResultPoint2[1];
	(*vn)[2]=ResultPoint2[2];
	vCn++;
	vn++;
}
*/

return true;

}
