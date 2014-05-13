#include <stdio.h>
#include <g3x.h>



typedef struct Shape
{
	G3Xpoint *vrtx;/*pointeurs vers les tableaux du vertex canonique*/
	G3Xvector *norm;/*pointeurs vers les tableaux du normales canonique*/

	G3Xcolor col; /*Couleur*/
  	int ID; /*type*/
	double ambi, diff, spec, shine, alpha; /*materiau*/
	int pointNo;
	bool initialized;
} Shape;


/*Mise à jour des coordonnées de la Shape après application de la matrice
constituée par la multiplication de toutes les matrices précédentes */

bool UpdateShape(Shape * str,  double *ptr_Mat){
	G3Xpoint *v2=str->vrtx;
	G3Xpoint *vn=str->norm;
	int q;
	q=0;

	G3Xpoint ResultPoint;

	for (q = 0; q < str->pointNo; ++q){
		g3x_ProdHMatPoint(ptr_Mat, *v2, ResultPoint);
		(*v2)[0]=ResultPoint[0];
		(*v2)[1]=ResultPoint[1];
		(*v2)[2]=ResultPoint[2];
		v2++; 
	}
	

	return true;

}