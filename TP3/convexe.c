#include "convexe.h"

double myRandom (double a, double b)
{
    double tmp = random(); /* long int in [0, RAND_MAX] */

    return a+tmp*((b-a)/RAND_MAX);
}

void winInit()
{
    gluOrtho2D(minX, maxX, minY, maxY) ;
}

void generation()
{
    int n = nbPoints ;

    while (--n >= 0)
    {
        P[n].coords[0] = myRandom(minX+margin, maxX-margin) ;
        P[n].coords[1] = myRandom(minY+margin, maxY-margin) ;
    }
}

int cestDansLaBoite(vertex *a, vertex *b, vertex *c)
{
    double xMin = MIN(a->coords[0], b->coords[0]) ;
    double yMin = MIN(a->coords[1], b->coords[1]) ;
    double xMax = MAX(a->coords[0], b->coords[0]) ;
    double yMax = MAX(a->coords[1], b->coords[1]) ;
    if((xMin <= c->coords[0]) && (xMax >= c->coords[0]) && (yMin <= c->coords[1]) && (yMax >= c->coords[1]))
        return VRAI ;
    return FAUX ;
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

void cubinit()
{
    int i, j, k ;
    int puiss ;
    int puissEnreg ;
    int unCote ;
    generation() ;

    for(i = 0; i < nbPoints-1; i++)
    {
        for(j = (i + 1); j < nbPoints; j++)
        {
            puissEnreg = ALIGNE;
            unCote = VRAI;

            for(k = 0; k < nbPoints; k++)
            {
                puiss = puissance(&P[i], &P[j], &P[k]) ;
                if(puiss == ALIGNE)
                {
                    if(!cestDansLaBoite(&P[i], &P[j], &P[k]))
                    {
                        unCote = FAUX ;
                        break;
                    }
                }
                else
                {
                    if(puissEnreg != puiss)
                    {
                        if(puissEnreg != ALIGNE)
                        {
                            unCote = FAUX ;
                            break;
                        }
                        else
                            puissEnreg = puiss ;
                    }
                }
            }
            if(unCote)
            {
                if(nbSegm >= nbSegmMax)
                {
                    nbSegmMax++ ;
                    S = realloc (S, nbSegmMax * sizeof(segm)) ;
                }
                S[nbSegm].points[0] = i ;
                S[nbSegm].points[1] = j ;
                nbSegm++ ;
                glutPostRedisplay() ;
            }
        }
    }
}

void display(void)
{
    glColor3f(0.0, 0.0, 0.0) ;
    glClear(GL_COLOR_BUFFER_BIT) ;
    glEnd() ;
    glFlush() ;
}

int main(int argc, char **argv)
{
    int c;

    opterr = 0;
    while ((c = getopt(argc, argv, "m:n:")) != EOF)
    {
        switch (c)
        {
        case 'm' : if (((sscanf(optarg, "%d", &cubique) != 1) || cubique < 0) || cubique > 1)
            cubique = 0 ;
            break;
        case 'n': if ((sscanf(optarg, "%d", &nbPoints) != 1) || nbPoints <= 0)
            nbPoints = 50 ;
            break;
        case '?': printf("use option -nX (no space), with 0 < X.\n") ;
            break;
        default : printf("Shouldn't be here, really...\n") ;
            break;
        }
    }

    P = calloc(nbPoints, sizeof(vertex)) ;
    S = calloc(nbSegmMax, sizeof(segm)) ;

    printf("cubique : %d\n", cubique) ;
    printf("nbPoints : %d\n", nbPoints) ;

    glutInit(&argc, argv) ;
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA) ;

    glutInitWindowPosition(5,5) ;
    glutInitWindowSize(300,300) ;

    glutCreateWindow("Enveloppe convexe") ;
    winInit() ;

    if(cubique)
        cubinit() ;
    //glutMouseFunc(generation) ;

    glutDisplayFunc(display) ;
    glutMainLoop() ;

    return EXIT_SUCCESS ;
}
