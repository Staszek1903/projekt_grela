#ifndef GUIBITMAP_H
#define GUIBITMAP_H

#include "guinode.h"
#include "Screen.h"

class GuiBitmap : public GuiNode, public Bitmap
{
    Screen & screen;
public:
    GuiBitmap(int x,int y, Screen & screen);
    virtual void update(GuiEvent *) override;
    virtual void draw() override;
};

#endif // GUIBITMAP_H
