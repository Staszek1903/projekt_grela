#ifndef GUIPALLETE_H
#define GUIPALLETE_H

#include "guinode.h"
#include "algorytmy.h"
#include <vector>

class GuiPallete : public GuiNode
{
    Screen & screen;
    Pallete palety[4];
    int active;
    bool setted = false;
public:
    GuiPallete(Screen & screen, int x, int y);
    void setGeneratedPalete(Pallete p);

    int getActive();
    void setActive(int active);
    Pallete getActivePallete();

    virtual void update(GuiEvent *) override;
    virtual void draw() override;
};

#endif // GUIPALLETE_H
