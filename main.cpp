#include <cstdlib>
#include <algorithm>

#ifdef __linux__
    #include <SDL/SDL.h>
    #include "include/Bitmap.h"
    #include "include/Screen.h"
    #include "include/algorytmy.h"
    #include "include/button.h"
    #include "include/guimanager.h"
    #include "include/sdlbutton.h"
#else
    #include <SDL.h>
    #include "Bitmap.h"
    #include "Screen.h"
    #include "algorytmy.h"
    #include "button.h"
    #include "guimanager.h"
    #include "sdlbutton.h"
#endif

using namespace std;

//TODO event handlers
//TODO class BUTTON
//TODO copy constructors;

int main ( int argc, char** argv )
{
    Screen screen(900,600,"projekt_grela");
    GuiManager manager;
    Button * button = (Button *)manager.addNode(new Button),
            * button2 = (Button *)manager.addNode(new Button);
    button->setPosition(300,300);
    button2->setPosition(200,200);
    button->setDimensions(200,50);
    button2->setDimensions(200,50);
    button->setName("BUTTON");
    button->setDrawer(new ButtonDrawer(screen, {200,100,50}));
    button2->setDrawer(new ButtonDrawer(screen, {50,100,200}));
    button->setHandler(new ButtonHandler());
    button2->setHandler(new ButtonHandler());

    screen.clear({171,200,50});


    Uint32 start_ticks = SDL_GetTicks();

    // program main loop
    bool done = false;
    while (!done)
    {
        Uint32 new_ticks = SDL_GetTicks();
        if((new_ticks - start_ticks)>50)
        {
            manager.draw();
            start_ticks = new_ticks;
        }

        // message processing loop
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            GuiEvent ev;
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

                    ev.char_clicked = event.key.keysym.sym;

                    printf("key: %i %c\n", ev.char_clicked, (char)ev.char_clicked);

                    // exit if ESCAPE is pressed
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                        done = true;
                    if (event.key.keysym.sym == SDLK_1) test1(screen);
                    if (event.key.keysym.sym == SDLK_2) test2(screen);
                    if (event.key.keysym.sym == SDLK_3) test3(screen);
                    if (event.key.keysym.sym == SDLK_4) test4(screen);
                    if (event.key.keysym.sym == SDLK_5) test5(screen);
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

            case SDL_MOUSEMOTION:
                ev.mouse_x = event.motion.x;
                ev.mouse_y = event.motion.y;
                break;

            case SDL_MOUSEBUTTONDOWN:
                //printf("Mouse click: %i %i\n", event.motion.x, event.motion.y);
                ev.mouse_x = event.motion.x;
                ev.mouse_y = event.motion.y;
                ev.mouse_pressed = true;
                break;

            case SDL_MOUSEBUTTONUP:
                ev.mouse_x = event.motion.x;
                ev.mouse_y = event.motion.y;
                ev.mouse_released = true;
                break;
            } // end switch

            manager.update(&ev);
        } // end of message processing

        screen.flip();
        //printf("flip");
    } // end main loop


    // all is well ;)
    printf("Exited cleanly\n");
    return 0;
}
