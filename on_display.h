

static void on_display(void) /* prikazivanje svih elemenata na prozoru */
{
    glClear(GL_COLOR_BUFFER_BIT);
    if(pictures_read==NO) /* ako nisu ucitane slike, moramo ih ucitati */
        ucitaj_slike();

    /* prikazivanje raznih elemenata na prozoru */
    pozadina_display();
    brod_display();
    meteori_display();
    sudar_display();
    energy_display();
    health_display();
    score_display();

    glutSwapBuffers();
    return;
}

static void energy_display() /* koliko energije imamo za laser */
{
    int i;
    char string[10];
    glBegin(GL_QUADS);
        glColor4f(0,210/255.0,1,1);
        glVertex2f(-0.7,0.94);
        glVertex2f(-0.7+space_ship.energy/200.0,0.94);
        glVertex2f(-0.7+space_ship.energy/200.0,0.9);
        glVertex2f(-0.7,0.9);
    glEnd();

    /* Postavljamo tekst za Energy */
    glColor4f(0,210/255.0,1,1);
    glRasterPos2f(-0.99, 0.9);
    sprintf(string,"ENERGY:");
    for (i = 0; i < 7; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
    return;
}


static void health_display() /* koliko health nam je preostalo */
{
    int i;
    char string[10];
    glBegin(GL_QUADS);
        glColor4f(1,0,0,1);
        glVertex2f(-0.7,0.99);
        glVertex2f(-0.7+space_ship.health/200.0,0.99);
        glVertex2f(-0.7+space_ship.health/200.0,0.95);
        glVertex2f(-0.7,0.95);
    glEnd();

    /* Postavljamo tekst za health */
    glColor4f(1,0,0,1);
    glRasterPos2f(-0.99, 0.95);
    sprintf(string,"HEALTH:");
    for (i = 0; i < 7; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
    return;
}

static void score_display() /* Postavljamo tekst za score */
{
    int i;
    char string[10];
    glColor4f(1,1,1,1);
    glRasterPos2f(0.6, 0.95);
    sprintf(string,"SCORE:   ");
    for (i = 0; i < 10; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);

    /* postavljamo konkretan score */
    glRasterPos2f(0.6, 0.9);
    sprintf(string,"%.10d",space_ship.score);
    for (i = 0; i < 10; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
    return;
}


static void pozadina_display() /* Postavljamo pozadinu koja se pomera */
{
    /* dva puta, da bi izgledala kao animacija */
    texture_display(back-1.0,0,1,1,POZADINA);
    texture_display(back+1.0,0,1,1,POZADINA);
    return;
}

static void brod_display() /* Postavljamo svemirski brod */
{
    int i;
    texture_display(space_ship.x,space_ship.y,0.1,0.1,BROD);

    /* postavljanje lasera koji postoje */
    for(i=0;i<MAX_LASER;i++)
        if(projektili[i].exists==YES)
        {
            glBegin(GL_QUADS);
                glColor4f(0,210/255.0,1,1);
                glVertex2f(projektili[i].x,projektili[i].y-0.003);
                glVertex2f(projektili[i].x+0.05,projektili[i].y-0.003);
                glVertex2f(projektili[i].x+0.05,projektili[i].y+0.003);
                glVertex2f(projektili[i].x,projektili[i].y+0.003);
            glEnd();
        }
    return;
}


static void meteori_display() /* postavljamo meteore koji postoje */
{
    int i;
    for(i=0;i<MAX_METEORI;i++)
        if(meteori[i].x<1.3 && meteori[i].exists==YES)
            texture_display(meteori[i].x,meteori[i].y,meteori[i].size*METEOR_SIZE,meteori[i].size*METEOR_SIZE,METEOR);
    return;
}


static void sudar_display() /* postavljamo animaciju dima, ako postoji */
{
    int i;
    for(i=0;i<MAX_DIM;i++)
        if(dim_pri_sudaru[i].vreme>0)
        {
            float t=dim_pri_sudaru[i].vreme/500.0;
            texture_display(dim_pri_sudaru[i].x,dim_pri_sudaru[i].y,t,t,DIM);
        }
    return;
}


/* posebno obradjujemo texture */
static void texture_display(float x,float y,float vx,float vy,int ID)
{
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindTexture(GL_TEXTURE_2D,ID);
    glEnable(GL_TEXTURE_2D);
    glColor4f(1,1,1,1);
    glBegin(GL_QUADS);
        glTexCoord2f(1,1);
        glVertex2f(x+vx,y+vy);
        glTexCoord2f(1,0);
        glVertex2f(x+vx,y-vy);
        glTexCoord2f(0,0);
        glVertex2f(x-vx,y-vy);
        glTexCoord2f(0,1);
        glVertex2f(x-vx,y+vy);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    return;
}
