#include <GL/glut.h>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include "definicije.h"
#include "keyboard.h"
#include "ucitavanje_slike.h"
#include "on_time.h"
#include "on_display.h"


int main(int argc,char** argv)
{
    srand(time(NULL)); /* pocetna vrednost za random */
    inicijalizacija(); /* inicijalizacija igre */
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(0,0);
    glutCreateWindow("SpaceShip");
    glutDisplayFunc(on_display);

    /* ukljucujemo obe funkcije za animaciju kretanja */
    glutKeyboardFunc(key_down);
    glutKeyboardUpFunc(key_up);

    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_EQUAL,1); /* za izbacivanje delove slika gde je alpha 1.0 */
    glClearColor(0,0,0,0);
    glutMainLoop();
    return 0;
}
