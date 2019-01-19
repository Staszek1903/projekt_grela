#ifdef __linux__
    #include "include/Screen.h"
    #include "SDL/SDL_ttf.h"
#else
    #include "Screen.h"
    #include "SDL_ttf.h"
#endif

Screen::Screen(int width, int height, std::string name)
{
    // console output
    //freopen( "CON", "wt", stdout );
    //freopen( "CON", "wt", stderr );

    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return;
    }

    if ( TTF_Init() <0 )
    {
        printf( "Unable to init TTF: %s\n", TTF_GetError() );
        return;
    }

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

    SDL_Quit();
    TTF_Quit();
}

void Screen::flip()
{
    SDL_Flip(surface);
}
