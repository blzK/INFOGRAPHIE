
#define N 200
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
static G3Xcolor vertKaki   ={35./255.,77./255.,32./255.};
static G3Xcolor grisMetal   ={0.0,1.0,0.0};
static G3Xcolor cyan   ={0.0,1.0,1.0};
static G3Xcolor bleu   ={0.0,0.0,1.0};
static G3Xcolor magenta={1.0,0.0,1.0};

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