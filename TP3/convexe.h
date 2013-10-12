#ifndef __CONVEXE_H__
#define CONVEXE_H__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <unistd.h>
#include <GL/glut.h>

/*! variable externe permettant de lire les parametres sur le ligne de commande.*/
extern char *optarg;

/*! bascule pour autoriser ou interdire (0) les messages d'erreurs envoyes par getopt. */
extern int opterr;

/*! Dimension de l'espace */
#define DIM 2

#define VRAI 1
#define FAUX 0
#define ADROITE 0
#define AGAUCHE 1
#define ALIGNE 2

#define MAX(x,y) (((x) > (y)) ? (x) : (y))
#define MIN(x,y) (((x) < (y)) ? (x) : (y))

/*! Structure pour representer un point. */
typedef struct
{
  double coords[DIM];
} vertex;

typedef struct
{
  int points[DIM];
} segm;

/*! Tailles diverses du systemes de fenetrage .*/
const double minX = 0,
             maxX = 500,
             minY = 0,
             maxY = 500,
             margin = 10;

int nbPoints = 50;
int cubique = 1;
int nbSegmMax = 3;
int nbSegm = 0;

vertex *P = NULL;
segm *S = NULL;
#endif
