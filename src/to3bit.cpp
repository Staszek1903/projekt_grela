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
            tab[indeks++] = FindIndex(in.getPixel(i,j), paleta);
        }
    return tab;
}

void test4(Screen & screen)
{
    Bitmap bmp("obrazek1.bmp");
    Bitmap bmp1("obrazek1.bmp");
    Bitmap bmp2("obrazek1.bmp");
    screen.draw(bmp,0,0);
    Pallete paleta = getPallete(bmp);
    to3bitBMP(bmp, bmp1, paleta);
    screen.draw(bmp1, 0, 300);
    paleta = NarzuconaPaleta();
    to3bitBMP(bmp, bmp2,paleta);
    screen.draw(bmp2, 450, 0);
}
