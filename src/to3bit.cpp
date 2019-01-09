#include "algorytmy.h"
#include <math.h>

using namespace std;

Pallete NarzuconaPaleta()
{
Pallete narzuconaPaleta;
narzuconaPaleta.c[0].r = 255;
narzuconaPaleta.c[0].g = 255;
narzuconaPaleta.c[0].b = 255;

narzuconaPaleta.c[1].r = 0;
narzuconaPaleta.c[1].g = 0;
narzuconaPaleta.c[1].b = 0;

narzuconaPaleta.c[2].r = 255;
narzuconaPaleta.c[2].g = 0;
narzuconaPaleta.c[2].b = 0;

narzuconaPaleta.c[3].r = 0;
narzuconaPaleta.c[3].g = 255;
narzuconaPaleta.c[3].b = 0;

narzuconaPaleta.c[4].r = 0;
narzuconaPaleta.c[4].g = 0;
narzuconaPaleta.c[4].b = 255;

narzuconaPaleta.c[5].r = 255;
narzuconaPaleta.c[5].g = 255;
narzuconaPaleta.c[5].b = 0;

narzuconaPaleta.c[6].r = 0;
narzuconaPaleta.c[6].g = 255;
narzuconaPaleta.c[6].b = 255;

narzuconaPaleta.c[7].r = 255;
narzuconaPaleta.c[7].g = 0;
narzuconaPaleta.c[7].b = 255;
return narzuconaPaleta;
}

Pallete SkalaSzarosci()
{
    Pallete paleta;
paleta.c[0].r = 0;
paleta.c[0].g = 0;
paleta.c[0].b = 0;

paleta.c[1].r = 36;
paleta.c[1].g = 36;
paleta.c[1].b = 36;

paleta.c[2].r = 72;
paleta.c[2].g = 72;
paleta.c[2].b = 72;

paleta.c[3].r = 108;
paleta.c[3].g = 108;
paleta.c[3].b = 108;

paleta.c[4].r = 144;
paleta.c[4].g = 144;
paleta.c[4].b = 144;

paleta.c[5].r = 180;
paleta.c[5].g = 180;
paleta.c[5].b = 180;

paleta.c[6].r = 216;
paleta.c[6].g = 216;
paleta.c[6].b = 216;

paleta.c[7].r = 255;
paleta.c[7].g = 255;
paleta.c[7].b = 255;
return paleta;
}

SDL_Color FindColor(SDL_Color pixel, Pallete paleta)
{
    int minDistance = 1000;
    int minIndeks = 0;
    for(int i = 0; i < 8; ++i)
    {
        int distance = sqrt(pow(pixel.r - paleta.c[i].r, 2) + pow(pixel.g - paleta.c[i].g, 2) + pow(pixel.b - paleta.c[i].b, 2));
        if (distance < minDistance)
        {
            minDistance = distance;
            minIndeks = i;
        }
    }
    return paleta.c[minIndeks];
}

int FindIndex(SDL_Color pixel, Pallete paleta)
{
    int minDistance = 1000;
    int minIndeks = 0;
    for(int i = 0; i < 8; ++i)
    {
        int distance = sqrt(pow(pixel.r - paleta.c[i].r, 2) + pow(pixel.g - paleta.c[i].g, 2) + pow(pixel.b - paleta.c[i].b, 2));
        if (distance < minDistance)
        {
            minDistance = distance;
            minIndeks = i;
        }
    }
    return minIndeks;
}

void to3bitBMP(Bitmap &in, Bitmap &out, Pallete paleta)
{
    int resX = in.getWidth();
    int resY = in.getHeight();

    for(int i = 0; i < resX; ++i)
        for(int j = 0; j < resY; ++j)
        {
            out.setPixel(i,j, FindColor(in.getPixel(i,j), paleta));
        }
}

int* to3bitTab(Bitmap &in, Pallete paleta)
{
    int resX = in.getWidth();
    int resY = in.getHeight();
    int* tab = new int[resX * resY];
    int indeks = 0;
    for(int i = 0; i < resX; ++i)
        for(int j = 0; j < resY; ++j)
        {
            tab[indeks++] = FindIndex(in.getPixel(j,i), paleta);
        }
    return tab;
}

void test4(Screen & screen)
{
    Bitmap bmp("obrazek4.bmp");
    Bitmap bmp1("obrazek4.bmp");
    Bitmap bmp2("obrazek4.bmp");
    Bitmap bmp3("obrazek4.bmp");
    screen.draw(bmp,0,0);
    Pallete paleta;

    paleta = getPallete(bmp);
    to3bitBMP(bmp, bmp1, paleta);
    screen.draw(bmp1, bmp1.getWidth(), 0);

    paleta = NarzuconaPaleta();
    to3bitBMP(bmp, bmp2,paleta);
    screen.draw(bmp2, 0, bmp2.getHeight());

    paleta = SkalaSzarosci();
    to3bitBMP(bmp, bmp3, paleta);
    screen.draw(bmp3, bmp3.getWidth(), bmp3.getHeight());
}
