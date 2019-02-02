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
    int active;

public:
    GuiBitmap(int x,int y, Screen & screen);
    Bitmap & setOiginal(const Bitmap & bmp);
    Bitmap & set3bit(const Bitmap & bmp);
    Bitmap & getOriginal();
    Bitmap & get3bit();
    Bitmap & getActive();

    void setActive(int);
    virtual void update(GuiEvent *) override;
    virtual void draw() override;
};

#endif // GUIBITMAP_H
