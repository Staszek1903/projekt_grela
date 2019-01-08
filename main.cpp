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



int main ( int argc, char** argv )
{
    Screen screen(800,700,"projekt_grela");

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
