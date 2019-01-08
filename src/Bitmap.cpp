#include "include/Bitmap.h"

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
        int bpp = surface->format->BytesPerPixel;

        Uint8 *p = (Uint8 *)surface->pixels + y * (surface->pitch) + x*bpp;
        Uint32 pixel = SDL_MapRGB(surface->format, color.r,color.g,color.b);

        switch(bpp)
        {
        case 1:
            *p = (Uint8)pixel;
            break;
        case 2:
            *(Uint16 *)p = (Uint16)pixel;
            break;
        case 3:
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
                p[0] = (pixel >> 16) & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = pixel & 0xff;
            } else {
                p[0] = pixel & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = (pixel >> 16) & 0xff;
            }
            break;
        case 4:
            *(Uint32 *)p = pixel;
            break;
        }
    }
}

SDL_Color Bitmap::getPixel(int x, int y)
{
    SDL_Color color = {0,0,0};

    if ((x>=0) && (x<getWidth()) && (y>=0) && (y<getHeight()))
    {
        Uint8 *p = (Uint8 *)surface->pixels + y * (surface->pitch) + x*surface->format->BytesPerPixel;
        Uint32 color_raw = *(Uint32 *)p;
        SDL_GetRGB(color_raw, surface->format, &color.r, &color.g, &color.b);

    }

    return color;
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
                                   24,
                                   0,0,0,0);
    if (!surface)
    {
        printf("Unable to create bitmap: %s\n", SDL_GetError());
    }
}

