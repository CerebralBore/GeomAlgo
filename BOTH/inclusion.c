#include "inclusion.h"

extern char *optarg;
extern int opterr;

#define AGAUCHE 0
#define ADROITE 1
#define ALIGNE 2

#define DEDANS 0
#define DEHORS 1
#define SUR 2

double myRandom (double a, double b)
{
  double tmp = random(); /* long int in [0, RAND_MAX] */

  return a+tmp*((b-a)/RAND_MAX);
}

void selectPoints (void)
{
  int n = nbPoints;

  while (--n > 0)
   {
     P[n].coords[0] = myRandom(minX+10, maxX-10);
     P[n].coords[1] = myRandom(minY+10, maxY-10);
   }
   // P[0] mis à la main pour le voir sur un segment du triangle
   P[0].coords[0] = 50.0;
   P[0].coords[1] = 20.0;
}

int puissance(vertex *a, vertex *b, vertex *c)
{
	double A = b->coords[1] - a->coords[1];
	double B = a->coords[0] - b->coords[0];
	double C = -(B * a->coords[1] + A * a->coords[0]);
	double value = (A*c->coords[0] + B*c->coords[1] + C) / sqrt(A*A + B*B);
	//printf("A: %f, B: %f, C: %f, value: %f ", A, B, C, value);
	if(value < 0) return ADROITE;
	else if(value > 0) return AGAUCHE;
	else return ALIGNE;
}

void assertVertex(vertex *v0, vertex *v1, vertex *v2)
{
  T[0].coords[0] = v0->coords[0];
  T[0].coords[1] = v0->coords[1];
  T[1].coords[0] = v1->coords[0];
  T[1].coords[1] = v1->coords[1];
  T[2].coords[0] = v2->coords[0];
  T[2].coords[1] = v2->coords[1];
}

int inTriangle(vertex *i, vertex *j, vertex *k, vertex *x)
{
	int a, b, c;
	
	a = puissance(i, j, x);
	b = puissance(j, k, x);
	c = puissance(k, i, x);

	if((a == b) && (b == c))   
	{
		return DEDANS;
	}
	else if((a == ALIGNE && (b == c)) || (b == ALIGNE && (a == c)) || (c == ALIGNE && (a == b)))   
	{
		return SUR;
	}
	else   
	{
		return DEHORS;
	}	
} 

void winInit (void)
{
  gluOrtho2D(0.0, 200, 0.0, 200);
}

void display(void)
{
  int n = nbPointsPolygon;
  int m = nbPoints;

  glColor3f(0.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0.0, 0.0, 1.0);
		
  switch (displayChoice)
  {
		  case 0: glBegin(GL_POINTS);
				  break;
		  case 1: glBegin(GL_LINES);
				  break;
		  case 2: glBegin(GL_LINE_STRIP);
				  break;
		  case 3: glBegin(GL_LINE_LOOP);
				  break;
		  default: glBegin(GL_POLYGON);
				  break;
  }

  while (--n >= 0)
   glVertex2f(T[n].coords[0], T[n].coords[1]);
  glEnd();

  glBegin(GL_POINTS);
  while (--m >= 0)
	{
		switch (inTriangle(&T[0], &T[1], &T[2], &P[m]))
		{
			case DEDANS:	glColor3f(0.0, 1.0, 0.0);
							glVertex2f(P[m].coords[0], P[m].coords[1]);
							break;
							
			case SUR:		glColor3f(1.0, 1.0, 1.0);
							glVertex2f(P[m].coords[0], P[m].coords[1]);
							break;
						
			case DEHORS: 	glColor3f(1.0, 0.0, 0.0);
							glVertex2f(P[m].coords[0], P[m].coords[1]);
							break;
							
			default:		break;
		}
	}
  glEnd();

  glFlush();
}

int main(int argc, char **argv)  
{  
  int c;

  P = (vertex *) malloc(sizeof(vertex)*nbPoints);
  T = (vertex *) malloc(sizeof(vertex)*nbPointsPolygon);

  vertex v0;
  vertex v1;
  vertex v2;

  v0.coords[0] = 50.0;
  v0.coords[1] = 0;
  v1.coords[0] = 50.0;
  v1.coords[1] = 175.0;
  v2.coords[0] = 150.0;
  v2.coords[1] = 80.0;
  printf("value returned = %i \n", puissance(&v0, &v1, &v2));
  assertVertex(&v0, &v1, &v2);

  // question 2)c)
  // puissance(O,A,B)
  v0.coords[0] = 0.0;
  v0.coords[1] = 0.0;
  v1.coords[0] = 50.0;
  v1.coords[1] = 0.0;
  v2.coords[0] = 50.0;
  v2.coords[1] = 50.0;
  printf("value returned = %i \n", puissance(&v0, &v1, &v2));
  //assertVertex(&v0, &v1, &v2);

  //puissance (O,B,A)
  v0.coords[0] = 0.0;
  v0.coords[1] = 0.0;
  v1.coords[0] = 50.0;
  v1.coords[1] = 50.0;
  v2.coords[0] = 50.0;
  v2.coords[1] = 0.0;
  printf("value returned = %i \n", puissance(&v0, &v1, &v2));
  //assertVertex(&v0, &v1, &v2);
  // on constate qu'inverser les deux points fait que le point ne se trouve pas du même côté de la droite
  // car le côté n'est plus orienté dans le même sens

  opterr = 0; /* set off std error messages in case wrong option is chosen */
  while ((c = getopt(argc, argv, "n:")) != EOF)
  {
	switch (c)
	{
		case 'n': if ((sscanf(optarg, "%d", &nbPoints) != 1) || nbPoints <= 0)
					nbPoints = 50;
				  break;
		case '?': printf("use option -nX (no space), with 0 < X.\n");
				  break;
		default : printf("Shouldn't be here, really...\n");
				  break;
	}
  }
  assert(nbPoints > 0);
  P = (vertex *) malloc(sizeof(vertex)*nbPoints);
  assert(P != NULL);

  assert(displayChoice >= 0 && displayChoice <= 4);
  printf("Executing %s with line option %d = %s.\n", argv[0], displayChoice, lineOption[displayChoice]);
  glutInit(&argc, argv);  
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);  

  glutInitWindowPosition(5,5);  
  glutInitWindowSize(300,300);  

  glutCreateWindow("My first OpenGL window...");  
  
  winInit();

  selectPoints();

  glutDisplayFunc(display);  

  glutMainLoop();  

 
  return EXIT_SUCCESS;  
}  
