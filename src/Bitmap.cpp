#include "Bitmap.h"

Bitmap::Bitmap(int width, int height)
{
    create(width, height);
}

Bitmap::Bitmap(std::string dir)
{
    loadBMP(dir);
}


Bitmap::~Bitmap()
{
    if(surface)
        SDL_FreeSurface(surface);
}


void Bitmap::draw(SDL_Surface * screen, int x, int y)
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;

    SDL_BlitSurface(surface,nullptr,screen,&rect);
}

void Bitmap::clear(SDL_Color color)
{
    SDL_FillRect(surface, 0, SDL_MapRGB(surface->format, color.r, color.g, color.b));
}

void Bitmap::setPixel(int x, int y, SDL_Color color)
{
    if ((x>=0) && (x<getWidth()) && (y>=0) && (y<getHeight()))
    {
        Uint32 pixel = SDL_MapRGB(surface->format, color.r, color.g, color.b);
        Uint32 *p = (Uint32 *)surface->pixels + y * (surface->pitch/4) + x;
        *p = pixel;
    }
}

SDL_Color Bitmap::getPixel(int x, int y)
{
    if ((x>=0) && (x<getWidth()) && (y>=0) && (y<getHeight()))
    {
        Uint8 *p = (Uint8 *)surface->pixels + y * (surface->pitch) + x*4;
        return {p[2],p[1],p[0]};
    }

    return {0,0,0};
}

int Bitmap::getWidth()
{
    return surface->w;
}

int Bitmap::getHeight()
{
    return surface->h;
}

Bitmap::Bitmap()
{

}

void Bitmap::loadBMP(std::string dir)
{
    surface = SDL_LoadBMP(dir.c_str());
    if (!surface)
    {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
    }
}

void Bitmap::create(int x,int y)
{
    surface = SDL_CreateRGBSurface(0,
                                   x,
                                   y,
                                   32,
                                   0,0,0,0);
    if (!surface)
    {
        printf("Unable to create bitmap: %s\n", SDL_GetError());
    }
}
