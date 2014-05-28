
int N =200;
#define P 200
#define T 1
#define U 50

static G3Xcolor orange={0.8,0.6,0.0,0.0};
static int n=100,p=100; /*tailles utiles, n parallèles, p méridiens*/
static double r=1;


/* des couleurs prédéfinies */  
static G3Xcolor rouge  ={1.0,0.0,0.0};
static G3Xcolor jaune  ={1.0,1.0,0.0};
static G3Xcolor vert   ={0.0,1.0,0.0};
static G3Xcolor cyan   ={0.0,1.0,1.0};
static G3Xcolor bleu   ={0.0,0.0,1.0};
static G3Xcolor magenta={1.0,0.0,1.0};

/* Couleurs définies */

/*Char*/
static G3Xcolor vertKaki   ={9./255.,94./255.,9./255.};
static G3Xcolor grisMetal   ={9./255.,120./255.,9./255.};

/*sol*/
static G3Xcolor marronMont   ={102./255.,51./255.,0./255.};
static G3Xcolor vertSol   ={102./255.,204./255.,0./255.};
static G3Xcolor vertFonce   ={11./255.,36./255.,7./255.};

/* paramètres géométriques */
static double angle= 0.00;
static double rayon= 0.66;
/* paramètres de lumière/matière */
static double alpha= 0.5;
static double ambi = 0.4;
static double diff = 0.2;
static double spec = 0.5;/*0.4;*/
static double shin = 0.1;/*0.5;*/

#define MAXCOL 25
static G3Xcolor colmap[MAXCOL];

static G3Xvector W={1.,2.,3.};
static double    b=0.1;