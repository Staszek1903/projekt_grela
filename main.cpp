#include <cstdlib>
#include <SDL.h>
#include <vector>
#include <algorithm>

using namespace std;

//TODO event handlers
//TODO class BUTTON
//TODO copy constructors;

#include "Bitmap.h"
#include "Screen.h"
#include "algorytmy.h"

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

void RysujPalete(SDL_Color* tab)
{
    for(int k = 0; k < 8; k++)
        for(int i = 0; i < 20; i++)
            for(int j = 0; j < 20; j++)
            {
                setPixel(500+20*k+i, 500+j, tab[k].r, tab[k].g, tab[k].b);
            }
}

SDL_Color* Paleta(int resX, int resY)
{
    // Tworzenie wektora z kolorami
    vector<SDL_Color> tabColor;
    for(int i = 0; i < resX;i++)
        for(int j = 0; j < resY; j++)
        {
            SDL_Color pixel = getPixel(i,j);
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
    SDL_Color paleta[8];
    for(int i = 0; i < 8; i++)
    {
        paleta[i] = averageColor(tabColor, tabColor.size()/8*i, tabColor.size()/8*(i+1));
    }
    
    RysujPalete(paleta);
    
    SDL_Flip(screen);
}


int main ( int argc, char** argv )
{
    Screen screen(800,600,"projekt_grela");

    // program main loop
    bool done = false;
    while (!done)
    {
        // message processing loop
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            // check for messages
            switch (event.type)
            {
                // exit if the window is closed
            case SDL_QUIT:
                done = true;
                break;

                // check for keypresses
            case SDL_KEYDOWN:
                {
                    // exit if ESCAPE is pressed
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                        done = true;
                    if (event.key.keysym.sym == SDLK_1) test1(screen);
                    if (event.key.keysym.sym == SDLK_2) test2(screen);
                    if (event.key.keysym.sym == SDLK_3) test3(screen);
                    if (event.key.keysym.sym == SDLK_4) test4(screen);
                    if (event.key.keysym.sym == SDLK_a)
                        {Bitmap bmp("obrazek1.bmp"); screen.draw(bmp,0,0);}
                    if (event.key.keysym.sym == SDLK_s)
                        {Bitmap bmp("obrazek2.bmp"); screen.draw(bmp,0,0);}
                    if (event.key.keysym.sym == SDLK_d)
                        {Bitmap bmp("obrazek3.bmp"); screen.draw(bmp,0,0);}
                    if (event.key.keysym.sym == SDLK_f)
                        {Bitmap bmp("obrazek4.bmp"); screen.draw(bmp,0,0);}
                    if (event.key.keysym.sym == SDLK_g)
                        {Bitmap bmp("obrazek5.bmp"); screen.draw(bmp,0,0);}
                    if (event.key.keysym.sym == SDLK_b)
                        screen.clear({100,100,100});          break;
                     }
            } // end switch
        } // end of message processing

        screen.flip();
    } // end main loop


    // all is well ;)
    printf("Exited cleanly\n");
    return 0;
}
