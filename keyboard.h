

static void key_down(unsigned char key,int x,int y)
{
    x=x; //Compiler error fix
    y=y; //Compiler error fix

    switch(key)
    {
        case 27: /* Ako smo stisnuli esc, prekidamo igru */
            exit(1);
            /*break;*/
        case 'r':
        case 'R': /* Start ili reset igre */
            if(space_ship.start==NO) /* Startujemo igru, ako nije pokrenuta */
            {
                space_ship.start=YES;
                glutTimerFunc(TIMER,on_timer,0);
            }
            if(space_ship.start==-1) /* Resetovanje igre, ako ste izgubili */
            {
                inicijalizacija();
                glutPostRedisplay();
            }
            break;
        case 't':
        case 'T': /* Zaustavljamo igru */
            if(space_ship.start==YES)
                space_ship.start=NO;
            break;
        case 'w':
        case 'W': /* gore pomeramo */
            sw=BUTTON_W;
            space_ship.vy=BRZINA_BRODA;
            break;
        case 's':
        case 'S': /* dole poemramo */
            sw=BUTTON_S;
            space_ship.vy=-BRZINA_BRODA;
            break;
        case 'd':
        case 'D': /* desno pomeramo */
            ad=BUTTON_D;
            space_ship.vx=BRZINA_BRODA;
            break;
        case 'a':
        case 'A': /* levo pomeramo */
            ad=BUTTON_A;
            space_ship.vx=-BRZINA_BRODA;
            break;
        case ' ': /* pucanje lasera */
            if(space_ship.energy>ENERGY_REDUCE) /* ako imamo dovoljno energije */
            {
                space_ship.energy=space_ship.energy-ENERGY_REDUCE;
                projektil=2;
            }
        /* break; */
    }
    return;
}


/* kada podignemo dugme, moramo ispitati, da li smo stisnuli posle toga drugo dugme */
static void key_up(unsigned char key,int x,int y)
{
    x=x; //Compiler error fix
    y=y; //Compiler error fix

    switch(key)
    {
        case 'w':
        case 'W': /* zaustavljamo po y osi */
            if(sw==BUTTON_W) /* ako smo zadnje po y stisnuli W */
                space_ship.vy=0.0;
            break;
        case 's':
        case 'S': /* zaustavljamo po y osi */
            if(sw==BUTTON_S) /* ako smo zadnje po y stisnuli S */
                space_ship.vy=0.0;
            break;
        case 'd':
        case 'D': /* zaustavljamo po x osi */
            if(ad==BUTTON_D) /* ako smo zadnje po x stisnuli D */
                space_ship.vx=0.0;
            break;
        case 'a':
        case 'A': /* zaustavljamo po x osi */
            if(ad==BUTTON_A) /* ako smo zadnje po x stisnuli A */
                space_ship.vx=0.0;
            /*break;*/
    }
    return;
}
