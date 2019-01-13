#include <cstdlib>
#include <algorithm>

#ifdef __linux__
    #include <SDL/SDL.h>
    #include "include/Bitmap.h"
    #include "include/Screen.h"
    #include "include/algorytmy.h"
    #include "include/button.h"
#else
    #include <SDL.h>
    #include "Bitmap.h"
    #include "Screen.h"
    #include "algorytmy.h"
    #include "button.h"
#endif


using namespace std;

//TODO event handlers
//TODO class BUTTON
//TODO copy constructors;

class ButtonDrawer: public GuiDrawer
{
    Screen * screen;
    SDL_Color color;
public:
    ButtonDrawer(Screen & screen, SDL_Color color) :screen(&screen), color(color) {}
    virtual void draw(GuiNode * node) override;
};

class ButtonHandler: public GuiHandler
{
public:
    virtual void handle(GuiNode * node) override;
};

void ButtonDrawer::draw(GuiNode * node)
{
    for(int i=node->x; i < node->x+node->w; ++i)
        for(int j=node->y; j < node->y+node->h; ++j)
            screen->setPixel(i,j,color);
}

void ButtonHandler::handle(GuiNode * node)
{
    printf("button pressed: %i %i\n", node->x, node->y);
}


int main ( int argc, char** argv )
{
    Screen screen(900,600,"projekt_grela");
    Button button, button2;
    button.setPosition(0,0);
    button2.setPosition(200,0);
    button.setDimensions(100,100);
    button2.setDimensions(100,100);
    button.setName("BUTTON");
    button.setDrawer(new ButtonDrawer(screen, {200,100,50}));
    button2.setDrawer(new ButtonDrawer(screen, {50,100,200}));
    button.setHandler(new ButtonHandler());
    button2.setHandler(new ButtonHandler());

    // program main loop
    bool done = false;
    while (!done)
    {
        // message processing loop
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            button.draw();
            button2.draw();
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
            case SDL_MOUSEBUTTONDOWN:
                //printf("Mouse click: %i %i\n", event.motion.x, event.motion.y);
                GuiEvent ev;
                ev.mouse_x = event.motion.x;
                ev.mouse_y = event.motion.y;
                button.update(&ev);
                button2.update(&ev);

            } // end switch
        } // end of message processing

        screen.flip();
        //printf("flip");
    } // end main loop


    // all is well ;)
    printf("Exited cleanly\n");
    return 0;
}
