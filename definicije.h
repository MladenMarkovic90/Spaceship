

/* umesto true i false */
#define YES 1
#define NO 0


/* konstante za dugmad */
#define BUTTON_W 1
#define BUTTON_S -1
#define BUTTON_D 1
#define BUTTON_A -1


/* ID za slike */
#define POZADINA 1
#define BROD 2
#define METEOR 3
#define DIM 4


/* maksimumi */
#define MAX_ENERGY 100
#define MAX_HEALTH 100
#define MAX_LASER 30
#define MAX_METEORI 1000
#define MAX_DIM 100


#define ENERGY_REDUCE 20 /* kolko energy skidamo kada pucamo */
#define TIMER 25 /* broj mili sekunda za timer funkciju */
#define BRZINA_BRODA 0.025 /* za x,y vektore svemirskog broda */
#define METEORS_PER_PERIOD 5 /* maksimalni broj meteora koji se pojave u nekom periodu */
#define METEOR_TIME 15 /* period poslekoga ce da se pojave novi meteori */
#define METEOR_SIZE 0.05 /* mnozi se sa size meteora */
#define BRZINA_METEORA 0.01 /* vektor po x osi */
#define POZADINA_TIMER 0.0005 /* vektor po x osi za pomeranje pozadine */
#define DIM_TIMER 10 /* kolko dugo traje animacija dima */
#define METEORI_RADIUS 0.033 /* radius meteora koji se mnozi sa size meteora */


typedef struct laser
{
    float x;
    float y;
    int exists;
}laser;


typedef struct meteor
{
    float x;
    float y;
    int size; /* velicina meteora */
    int exists;
    unsigned int score; /* koliko score donosi meteor */
}meteor;


typedef struct dim
{
    float x;
    float y;
    int vreme; /* koliko je preostalo od animacije */
}dim;


typedef struct brod
{
    float x;
    float y;
    float vx; /* Vektor svemirskog broda po X */
    float vy; /* Vektor svemirskog broda po Y */
    int health;
    int energy; /* energy je potreban za pucanje */
    int score; /* score koliki smo dostigli */
    int start; /* Promenljiva koja oznacava da li je pokrenuta igra */
}brod;


static void on_display(); /* funkcija koja prikazuje sadrzaj display funkcija */
/* funkcije za prikazivanje slika */
static void pozadina_display();
static void brod_display();
static void meteori_display();
static void sudar_display();
/* funkcija za koordinate texture */
static void texture_display(float x,float y,float vx,float vy,int ID);
/* funkcije za ispis texta i stanja */
static void energy_display();
static void health_display();
static void score_display();


static void slike(const char*,GLuint); /* Funkcija za ucitavanje slika */
static void ucitaj_slike(); /* ucitava razne slike pomocu funkcije slike */


/* reagovanje kada je dugme stisnuto i kada vise nije stisnuto */
static void key_down(unsigned char key,int x,int y);
static void key_up(unsigned char key,int x,int y);


static void on_timer(int id); /* razna izracunavanja za on_display */
static void inicijalizacija(); /* Inicijalizacija za start/reset igre */
/* funkcija za racunanje sudara pomocu jednacine kruga */
static int sudar(float x1,float y1,float x2,float y2,float r);


static void sudar_aviona(); /* racunanje da li je avion se sudario sa meteorom */
static void sudar_laser(); /* racunanje da li je laser se sudario sa meteorom */
static void on_time_meteor(); /* racunanje pozicija meteora */
static void on_time_laser(); /* racunanje pozicija lasera */


meteor meteori[MAX_METEORI]; /* Meteori */
int pictures_read=NO; /* Promenljiva za slike */
laser projektili[MAX_LASER]; /* Broj mogucih projektila */
int projektil; /* Da li smo pucali */
int sw; /* S ili W stisnuto */
int ad; /* A ili D stisnuto */
float back;	/* Pozicija background slike */
int time_meteor; /* kolko vremena je proslo od stvaranje zadnjih meteora */
brod space_ship; /* svemirski brod */
dim dim_pri_sudaru[MAX_DIM]; /* broj mogucih animacije dima */


/* neki koeficijenti */
static int Score[]={100,200,500,1000}; /* u zavisnosti od size meteora, kolko score daje */
static int Health_remove[]={1,2,5,10}; /* u zavisnosti od size meteora, kolko health skida */
static float brod_coef_x[]={-0.02,-0.02,0.09}; /* x-koordinate temena broda */
static float brod_coef_y[]={0.08,-0.08,0}; /* y-koordinate temena broda */


static void inicijalizacija(void) /* inicijalizacija svih promenljivih za start/reset igre */
{
    int i=0;
    for(i=0;i<MAX_LASER;i++)
        projektili[i].exists=NO;
    for(i=0;i<MAX_METEORI;i++)
        meteori[i].exists=NO;
    for(i=0;i<MAX_DIM;i++)
        dim_pri_sudaru[i].vreme=0;
    sw=ad=time_meteor=0;
    back=1.0;
    space_ship.x=-0.9;
    space_ship.y=0;
    space_ship.vx=0;
    space_ship.vy=0;
    space_ship.start=0;
    space_ship.health=MAX_HEALTH;
    space_ship.energy=MAX_ENERGY;
    space_ship.score=0;
    return;
}
