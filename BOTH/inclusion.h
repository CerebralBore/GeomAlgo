#ifndef __INCLUSION_H__
#define INCLUSION_H__

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

/*! Structure pour representer un point. */
typedef struct
{
  double coords[DIM];
} vertex;

/*! Tailles diverses du systemes de fenetrage .*/
const double minX = 0,
             maxX = 500,
	         minY = 0,
	         maxY = 500,
	         margin = 10;

/*! Nombre de "sites" dans le programme, modifiable par la ligne
 * de commande de la fonction main().
 */
int nbPointsPolygon = 3; //v0,v1,v2 
int nbPoints = 50;
int displayChoice = 4;

/*! Tableau gobal des sommets */
vertex *T = NULL;
vertex *P = NULL;

char *lineOption[] = { "GL_POINTS", "GL_LINES", "GL_LINE_STRIP", "GL_LINE_LOOP", "GL_POLYGON"};


#endif
