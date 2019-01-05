#include "algorytmy.h"
#include <vector>
#include <algorithm>
using namespace std;

bool sortCompRed(SDL_Color i, SDL_Color j)
{
    return(i.r<j.r);
}

bool sortCompGreen(SDL_Color i, SDL_Color j)
{
    return(i.g<j.g);
}

bool sortCompBlue(SDL_Color i, SDL_Color j)
{
    return(i.b<j.b);
}

int vectorIncludes(vector<SDL_Color> tab, SDL_Color col)
{
    for(int k = 0; k < tab.size(); k++)
        if(tab[k].r == col.r && tab[k].g == col.g && tab[k].b == col.b)
        {
            return k;
        }
    return -1;
}

SDL_Color averageColor(vector<SDL_Color> tab, int min, int max)
{
    int red = 0;
    int green = 0;
    int blue = 0;

    for(int i = min;i < max; i++)
    {
        red += tab[i].r;
        green += tab[i].g;
        blue += tab[i].b;
    }
    SDL_Color ret;
    ret.r = red/(max-min);
    ret.g = green/(max-min);
    ret.b = blue/(max-min);
    return ret;
}

Pallete getPallete(Bitmap & in)
{
    int resX = in.getWidth();
    int resY = in.getHeight();
    // Tworzenie wektora z kolorami
    vector<SDL_Color> tabColor;
    for(int i = 0; i < resX;i++)
        for(int j = 0; j < resY; j++)
        {
            SDL_Color pixel = in.getPixel(i,j);
            int k = vectorIncludes(tabColor, pixel);
            if(k == -1)
            {
                tabColor.push_back(pixel);
            }
        }

    // Wyznaczanie zakresu
    int redRange;
    int redMin = tabColor[0].r;
    int redMax = tabColor[0].r;
    int greenRange;
    int greenMin = tabColor[0].g;
    int greenMax = tabColor[0].g;
    int blueRange;
    int blueMin = tabColor[0].b;
    int blueMax = tabColor[0].b;
    for(int i = 0; i < tabColor.size(); i ++)
    {
        if(redMin > tabColor[i].r)
            redMin = tabColor[i].r;
        if(redMax < tabColor[i].r)
            redMax = tabColor[i].r;

        if(greenMin > tabColor[i].g)
            greenMin = tabColor[i].g;
        if(greenMax < tabColor[i].g)
            greenMax = tabColor[i].g;

        if(blueMin > tabColor[i].b)
            blueMin = tabColor[i].b;
        if(blueMax < tabColor[i].b)
            blueMax = tabColor[i].b;
    }

    // Sortowanie
    redRange = redMax - redMin;
    greenRange = greenMax - greenMin;
    blueRange = blueMax - blueMin;
    if(redRange > greenRange && redRange > blueRange)
        sort(tabColor.begin(), tabColor.end(), sortCompRed);
    else if (greenRange > redRange && greenRange > blueRange)
        sort(tabColor.begin(), tabColor.end(), sortCompGreen);
    else
        sort(tabColor.begin(), tabColor.end(),sortCompBlue);

    // Tworzenie palety
    Pallete paleta;
    for(int i = 0; i < 8; i++)
    {
        paleta.c[i] = averageColor(tabColor, tabColor.size()/8*i, tabColor.size()/8*(i+1));
    }

   return paleta;
}

void test3(Screen & screen)
{
    Bitmap bmp("obrazek4.bmp");
    Pallete paleta = getPallete(bmp);
    for(int k = 0; k < 8; ++k)
        for(int i = 0; i < 20; ++i)
            for(int j = 0; j < 20; ++j)
                bmp.setPixel(i,j,paleta.c[k]);
    screen.draw(bmp, 0, 0);
}
