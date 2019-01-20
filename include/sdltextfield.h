#ifndef SDLTEXTFIELD_H
#define SDLTEXTFIELD_H

#ifdef __linux__
    #include "include/textfield.h"
    #include "include/guidrawer.h"
    #include "include/guihandler.h"
    #include "include/Screen.h"
    #include "SDL/SDL_ttf.h"
#else
    #include "textfield.h"
    #include "guidrawer.h"
    #include "guihandler.h"
    #include "Screen.h"
    #include "SDL_ttf.h"
#endif

class TexFieldDrawer : public GuiDrawer
{
public:
    Screen * screen;
    Bitmap * field;
    SDL_Color color;
    TTF_Font * font;
    bool flash;

    TexFieldDrawer(Screen &screen, SDL_Color color);
    virtual ~TexFieldDrawer() override;

    virtual void draw(GuiNode *) override;
    void createField(std::string,int,int);
    void loadFont();
};

#endif // SDLTEXTFIELD_H
