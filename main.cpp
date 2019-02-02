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
    #include "include/textfield.h"
    #include "include/sdltextfield.h"
    #include "include/handlers.h"
#else
    #include <SDL.h>
    #include "Bitmap.h"
    #include "Screen.h"
    #include "algorytmy.h"
    #include "button.h"
 //   #include "guimanager.h"
    #include "sdlbutton.h"
    #include "textfield.h"
    #include "sdltextfield.h"
    #include "handlers.h"
#endif

#include <vector>
#include <cstdio>

class GuiManager
{
    std::vector <GuiNode *> nodes;
public:
    GuiNode * addNode(GuiNode *);
    void update(GuiEvent *);
    void draw();

    GuiManager();
    ~GuiManager();
};

using namespace std;

//TODO event handlers
//TODO class BUTTON
//TODO copy constructors;

int main ( int argc, char** argv )
{
    Screen screen(900,600,"projekt_grela");
    GuiManager manager;

    auto bitmap = (GuiBitmap *)manager.addNode((new GuiBitmap(screen.getWidth()/2,screen.getHeight()/2,screen)));
    auto textfield = (TextField *)manager.addNode(new TextField("File Name", 25,25,400,50, nullptr, new TexFieldDrawer(screen,{200,200,255})));
    manager.addNode(new Button("LOAD BMP",25,80,200,50,new OpenBmpHandler(*textfield,*bitmap), new ButtonDrawer(screen,{255,255,255})));
    manager.addNode(new Button("LOAD OKON",25,135,200,50,new OpenOkonHandler(*textfield,*bitmap), new ButtonDrawer(screen,{255,255,255})));
    manager.addNode(new Button("SAVE BMP",25,190,200,50,new SaveBmpHandler(*textfield,*bitmap), new ButtonDrawer(screen,{255,255,255})));
    manager.addNode(new Button("SAVE OKON",25,245,200,50,new ButtonHandler, new ButtonDrawer(screen,{255,255,255})));
    manager.addNode(new Button("TEST1",25,300,200,50,new ButtonHandler, new ButtonDrawer(screen,{255,255,255})));
    manager.addNode(new Button("TEST2",25,355,200,50,new ButtonHandler, new ButtonDrawer(screen,{255,255,255})));
    manager.addNode(new Button("TEST3",25,410,200,50,new ButtonHandler, new ButtonDrawer(screen,{255,255,255})));
    manager.addNode(new Button("TEST4",25,465,200,50,new ButtonHandler, new ButtonDrawer(screen,{255,255,255})));
    manager.addNode(new Button("TEST5",25,520,200,50,new ButtonHandler, new ButtonDrawer(screen,{255,255,255})));


    screen.clear({0,0,0});
    manager.draw();
    screen.flip();

    // program main loop
    bool done = false;
    while (!done)
    {

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
                    ev.char_clicked = event.key.keysym.sym;
            break;
                    //printf("key: %i %c\n", ev.char_clicked, (char)ev.char_clicked);

                    // exit if ESCAPE is pressed
//                    if (event.key.keysym.sym == SDLK_ESCAPE)
//                        done = true;
//                    if (event.key.keysym.sym == SDLK_1) test1(screen);
//                    if (event.key.keysym.sym == SDLK_2) test2(screen);
//                    if (event.key.keysym.sym == SDLK_3) test3(screen);
//                    if (event.key.keysym.sym == SDLK_4) test4(screen);
//                    if (event.key.keysym.sym == SDLK_5) test5(screen);
//                    if (event.key.keysym.sym == SDLK_a)
//                        {Bitmap bmp("obrazek1.bmp"); screen.draw(bmp,0,0);}
//                    if (event.key.keysym.sym == SDLK_s)
//                        {Bitmap bmp("obrazek2.bmp"); screen.draw(bmp,0,0);}
//                    if (event.key.keysym.sym == SDLK_d)
//                        {Bitmap bmp("obrazek3.bmp"); screen.draw(bmp,0,0);}
//                    if (event.key.keysym.sym == SDLK_f)
//                        {Bitmap bmp("obrazek4.bmp"); screen.draw(bmp,0,0);}
//                    if (event.key.keysym.sym == SDLK_g)
//                        {Bitmap bmp("obrazek5.bmp"); screen.draw(bmp,0,0);}
//                    if (event.key.keysym.sym == SDLK_b)
//                        screen.clear({100,100,100});          break;
//                     }

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
