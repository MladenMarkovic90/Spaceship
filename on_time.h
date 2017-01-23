

static void on_timer(int id) /* svaki period se izvrsava ova funkcija */
{
    id=id;
    int i;
    if(space_ship.start<=NO) /* Izlazimo jer smo zaustavili ili zavrsili */
        return;
    if(space_ship.health<=0) /* ako nam je brod unisten */
    {
        space_ship.health=0; /* postavljamo health na 0, zbog debagovanja */
        space_ship.start=-1; /* zavrsili smo igru */
        glutPostRedisplay();
        return;
    }
    if(space_ship.energy<MAX_ENERGY) /* ako nije energija na max, povecavamo je */
        space_ship.energy++;
    back=back-POZADINA_TIMER; /* pomeramo pozadinu */
    if(back<-1.0) /* ako smo prosli sa levom pozadinom prozor, postavljamo je na pocetak */
        back=1.0;
    space_ship.y=space_ship.y+space_ship.vy; /* Pomeramo svemirski brod po x osi */
    space_ship.x=space_ship.x+space_ship.vx; /* Pomeramo svemirski brod po y osi */

    /* debagovanje da ne bi izaslo van prozora */
    if(space_ship.x<-0.9)
        space_ship.x=-0.9;
    if(space_ship.x>0.9)
        space_ship.x=0.9;
    if(space_ship.y>0.8)
        space_ship.y=0.8;
    if(space_ship.y<-0.9)
        space_ship.y=-0.9;

    /* animacija dima ako postoji */
    for(i=0;i<MAX_DIM;i++)
        if(dim_pri_sudaru[i].vreme>0)
        {
            dim_pri_sudaru[i].x-=BRZINA_METEORA;
            dim_pri_sudaru[i].vreme--;
        }
    on_time_laser(); /* racunanje animacije lasera */
    on_time_meteor(); /* racunanje animacije meteora */
    sudar_laser(); /* racunanje da li je doslo do sudara lasera i meteora */
    sudar_aviona(); /* racunanje da li je doslo do sudara svemiraskog broda i meteora */
    glutPostRedisplay();
    glutTimerFunc(TIMER,on_timer,0);
    return;
}


static void on_time_laser() /* racunanje animacije lasera */
{
    int i;

    /* pomeramo laser koji postoji */
    for(i=0;i<MAX_LASER;i++)
    {
        if(projektili[i].x<=1.0 && projektili[i].exists==YES)
            projektili[i].x+=0.05;
        else
            projektili[i].exists=NO;
    }

    /* pravimo novi gornji laser*/
    for(i=0;i<MAX_LASER && projektil==2;i++)
        if(projektili[i].exists==NO)
        {
            projektil--;
            projektili[i].x=space_ship.x+0.1;
            projektili[i].y=space_ship.y+0.03;
            projektili[i].exists=YES;
        }

    /* pravimo novi donji laser */
    for(;i<MAX_LASER && projektil==1;i++)
        if(projektili[i].exists==NO)
        {
            projektil--;
            projektili[i].x=space_ship.x+0.1;
            projektili[i].y=space_ship.y-0.03;
            projektili[i].exists=YES;
        }
    return;
}


static void on_time_meteor() /* racunanje animacije meteora */
{
    int i,j;
    time_meteor++;

    /* pomeramo meteore koji postoje */
    for(i=0;i<MAX_METEORI;i++)
    {
        if(meteori[i].exists==1 && meteori[i].x>-1.5)
            meteori[i].x-=BRZINA_METEORA;
        else
            meteori[i].exists=0;
    }

    /* pravimo nove meteore ako je doslo vreme */
    if(time_meteor==METEOR_TIME)
    {
        j=abs(rand())%(METEORS_PER_PERIOD+1); /* broj novih meteora */
        for(i=0;i<MAX_METEORI && j;i++)
            if(meteori[i].exists==NO)
            {
                meteori[i].x=1.3;
                meteori[i].y=abs(rand())%10000/5000.0-1.0; /* 10000/5000.0 zbog windowsa */
                meteori[i].size=abs(rand())%4+1;
                meteori[i].exists=YES;
                meteori[i].score=Score[meteori[i].size-1];
                j--;
            }
        time_meteor=0; /* pocinjemo ispocetka da brojimo interval */
    }
    return;
}


static void sudar_laser() /* racunanje da li je doslo do sudara lasera i meteora */
{
    int i,j,k;
    for(i=0;i<MAX_METEORI;i++)
        if(meteori[i].exists==YES)
            for(j=0;j<MAX_LASER;j++)
            {
                if(projektili[j].exists==YES && meteori[i].exists==YES)
                /* ako je doslo do sudara */
                if(sudar(projektili[j].x+0.05,projektili[j].y,meteori[i].x,meteori[i].y,meteori[i].size*METEORI_RADIUS))
                {
                    projektili[j].exists=NO;
                    meteori[i].size--;
                    if(meteori[i].size==0) /* ako je meteor unisten */
                    {
                        meteori[i].exists=NO;
                        space_ship.score=space_ship.score+meteori[i].score;
                    }
                    /* svaki put kada je meteor pogodjen, pravimo animaciju dima */
                    for(k=0;k<MAX_DIM;k++)
                        if(dim_pri_sudaru[k].vreme<=0)
                        {
                            dim_pri_sudaru[k].vreme=DIM_TIMER*(meteori[i].size+1);
                            dim_pri_sudaru[k].x=projektili[j].x+0.05;
                            dim_pri_sudaru[k].y=projektili[j].y;
                            break;
                        }
                }
            }
    return;
}


static void sudar_aviona() /* racunanje da li je doslo do sudara svemiraskog broda i meteora */
{
    int i,j,k;
    float x1,y1,x2,y2,x3,y3;
    float ty1,ty2,ty3,tx1,tx2,tx3;

    /* koordinate temena aviona po glavnom trouglu */
    x1=space_ship.x+brod_coef_x[0];
    y1=space_ship.y+brod_coef_y[0];
    x2=space_ship.x+brod_coef_x[1];
    y2=space_ship.y+brod_coef_y[1];
    x3=space_ship.x+brod_coef_x[2];
    y3=space_ship.y+brod_coef_y[2];

    for(i=0;i<MAX_METEORI;i++)
    {
        if(meteori[i].exists==YES)
            for(j=0;j<=10;j++)
            {

                /* pomeramo tacke po jednacini prave za svake 2 tacke */
                tx1=x1+fabs(x1-x2)*j/10.0;
                ty1=y1-fabs(y1-y2)*j/10.0;
                tx2=x1+fabs(x1-x3)*j/10.0;
                ty2=y1-fabs(y1-y3)*j/10.0;
                tx3=x2+fabs(x3-x2)*j/10.0;
                ty3=y2+fabs(y3-y2)*j/10.0;

                /* ako je doslo do sudara */
                if(sudar(tx1,ty1,meteori[i].x,meteori[i].y,meteori[i].size*METEORI_RADIUS) ||
                    sudar(tx2,ty2,meteori[i].x,meteori[i].y,meteori[i].size*METEORI_RADIUS) ||
                    sudar(tx3,ty3,meteori[i].x,meteori[i].y,meteori[i].size*METEORI_RADIUS))
                {
                    /* smanjujemo health broda za koeficijent za trenutnu velicinu */
                    space_ship.health=space_ship.health-Health_remove[meteori[i].size-1];
                    meteori[i].exists=NO; /* meteor je unisten */

                    /* animacije dima kada se sudarimo sa meteorom */
                    for(k=0;k<MAX_DIM;k++)
                        if(dim_pri_sudaru[k].vreme<=0)
                        {
                            dim_pri_sudaru[k].vreme=DIM_TIMER*meteori[i].size;
                            dim_pri_sudaru[k].x=space_ship.x;
                            dim_pri_sudaru[k].y=space_ship.y;
                            break;
                        }
                    break;
                }
            }
    }
    return;
}


/* funkcija za racunanje sudara pomocu jednacine kruga */
static int sudar(float x1,float y1,float x2,float y2,float r)
{
    if(((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)-r*r)<0)
        return 1;
    return 0;
}
