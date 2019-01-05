#include "include/Screen.h"

Screen::Screen(int width, int height, std::string name)
{
    // console output
    //freopen( "CON", "wt", stdout );
    //freopen( "CON", "wt", stderr );

    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return;
    }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // create a new window
    surface = SDL_SetVideoMode(width, height, 32,
                                           SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !surface )
    {
        printf("Unable to set video: %s\n", SDL_GetError());
        return;
    }

    SDL_WM_SetCaption( name.c_str() , NULL );
}

Screen::~Screen()
{
    if(surface)
        SDL_FreeSurface(surface);
}

void Screen::flip()
{
    SDL_Flip(surface);
}

void Screen::draw(Bitmap &bitmap, int x, int y)
{
    bitmap.draw(surface,x,y);
}
