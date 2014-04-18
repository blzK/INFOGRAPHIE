#include <stdio.h>
#include <g3x.h>


  typedef struct{
  	double c[16];
  } HMat;

  typedef struct Shape
  {
	G3Xpoint *vrtx;/*pointeurs vers les tableaux du vertex canonique*/
	G3Xvector *norm;/*pointeurs vers les tableaux du normales canonique*/
	HMat Md, Mi, Mn; /*Matrices 4x4 directe, inverse, normale*/
	G3Xcolor col; /*Couleur*/
  	int ID; /*type*/
	double ambi, diff, spec, shine, alpha; /*materiau*/
  } Shape;
