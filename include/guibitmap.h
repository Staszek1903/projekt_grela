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
    std::vector <int> palletes_info;
    int active;

public:
    GuiBitmap(int x,int y, Screen & screen);
    Bitmap & addBitmap(const Bitmap &, int type_of_pallete);
    Bitmap & getBitmap(int);
    int getPalleteInfo(int);
    void setActive(int);
    virtual void update(GuiEvent *) override;
    virtual void draw() override;
};

#endif // GUIBITMAP_H
