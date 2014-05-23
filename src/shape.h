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
	int normNo; /*Nombre de normales*/
	double ratio;
} Shape;


