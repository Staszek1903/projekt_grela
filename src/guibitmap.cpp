#ifdef __linux__
    #include "include/guibitmap.h"
#else
    #include "guibitmap.h"
#endif


GuiBitmap::GuiBitmap(int x, int y, Screen &screen)
    :screen(screen),bitmaps(2), active(0)
{
    this->x = x;
    this->y = y;
}

Bitmap &GuiBitmap::setOiginal(const Bitmap &bmp)
{
    bitmaps.at(0) = bmp;
    active = 0;
    draw();

    return bitmaps.at(0);
}

Bitmap &GuiBitmap::set3bit(const Bitmap &bmp, Pallete pallete, TYPE_OF_PALLETE p)
{
    bitmaps.at(1) = bmp;
    active = 1;
    draw();

    bit3pallete = pallete;
    pallete_type = p;

    return bitmaps.at(1);
}

Bitmap &GuiBitmap::getOriginal()
{
    return bitmaps.at(0);
}

Bitmap &GuiBitmap::get3bit()
{
    return bitmaps.at(1);
}

Bitmap &GuiBitmap::getActive()
{
    return bitmaps.at(active);
}

Pallete GuiBitmap::getPallete()
{
    return bit3pallete;
}

TYPE_OF_PALLETE GuiBitmap::getPalleteType()
{
    return pallete_type;
}

void GuiBitmap::setActive(int a)
{
    active = (a>=bitmaps.size())? bitmaps.size()-1 : a;
    draw();
}

void GuiBitmap::update(GuiEvent *)
{

}

void GuiBitmap::draw()
{
    if(active < bitmaps.size())
    screen.draw(bitmaps.at(active),x,y);
}
