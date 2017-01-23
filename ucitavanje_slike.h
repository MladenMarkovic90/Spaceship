

static void ucitaj_slike() /* Funkcija koja sluzi za ucitavanje odredjenih slika */
{
    slike((char *)"svemir.image",POZADINA);
    slike((char *)"brod.image",BROD);
    slike((char *)"meteori.image",METEOR);
    slike((char *)"explode.image",DIM);
    pictures_read=YES; /* slike su ucitane */
    return;
}


static void slike(const char * s,GLuint ID) /* Funkcija koja ucitava slike u obliku .txt format */
{
    unsigned char header[10];
    unsigned int width=0, height=0;
    unsigned char * data;
    int i;
    FILE * file = fopen(s,"r");
    if(!file)
    {
        printf("Can't load %s\n",s);
        return;
    }
    fread(header, 1, 10, file);
    for(i=0;i<5;i++)
        width=width*10+header[i]-'0';
    for(i=5;i<10;i++)
        height=height*10+header[i]-'0';
    data=(unsigned char *)malloc(4*width*height*sizeof(unsigned char));
    fread(data,1,4*width*height,file);
    glBindTexture(GL_TEXTURE_2D,ID);
    glEnable(GL_TEXTURE_2D);
    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glDisable(GL_TEXTURE_2D);
    return;
}
