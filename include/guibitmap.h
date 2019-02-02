#ifndef GUIBITMAP_H
#define GUIBITMAP_H

#include "guinode.h"
#include "Screen.h"
#include <vector>
#include "algorytmy.h"

class GuiBitmap : public GuiNode
{
    Screen & screen;
    std::vector<Bitmap> bitmaps;
    Pallete bit3pallete;
    int active;

public:
    GuiBitmap(int x,int y, Screen & screen);
    Bitmap & setOiginal(const Bitmap & bmp);
    Bitmap & set3bit(const Bitmap & bmp, Pallete pallete);
    Bitmap & getOriginal();
    Bitmap & get3bit();
    Bitmap & getActive();
    Pallete getPallete();

    void setActive(int);
    virtual void update(GuiEvent *) override;
    virtual void draw() override;
};

#endif // GUIBITMAP_H
