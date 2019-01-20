#ifndef SDLBUTTON_H
#define SDLBUTTON_H

#ifdef __linux__
    #include <SDL/SDL_ttf.h>
    #include "include/guidrawer.h"
    #include "include/guihandler.h"
    #include "include/Screen.h"
    #include "include/button.h"
#else
    #include "guidrawer.h"
    #include "guihandler.h"
    #include "Screen.h"
    #include <SDL_ttf.h>
    #include "button.h"
#endif

#include <cmath>

class ButtonDrawer: public GuiDrawer
{
    Screen * screen;
    SDL_Color color;
    SDL_Surface * text;
    Bitmap * stand_by, *has_mouse, *clicked;
public:
    ButtonDrawer(Screen & screen, SDL_Color color);
    virtual ~ButtonDrawer() override;
    virtual void draw(GuiNode * node) override;

    void createText(std::string text);
    void createStandBy(int w, int h);
    void createHasMouse(int w, int h);
    void createCLicked(int w, int h);
};

class ButtonHandler: public GuiHandler
{
public:
    virtual void handle(GuiNode * node) override;
};

#endif // SDLBUTTON_H
