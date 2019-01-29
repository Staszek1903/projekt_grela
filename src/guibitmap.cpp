#ifdef __linux__
    #include "include/guibitmap.h"
#else
    #include "guibitmap.h"
#endif


GuiBitmap::GuiBitmap(int x, int y, Screen &screen)
    :screen(screen), active(0)
{
    this->x = x;
    this->y = y;
}

Bitmap &GuiBitmap::addBitmap(const Bitmap &bitmap, int type_of_pallete)
{
    bitmaps.push_back(bitmap);
    palletes_info.push_back(type_of_pallete);

    active = bitmaps.size()-1;


    draw();
    return bitmaps.at(active);
}

Bitmap &GuiBitmap::getBitmap(int index)
{
    index = (index < bitmaps.size())? index : 0;
    index = (index <0)? active : index;
    return bitmaps.at(index);
}

int GuiBitmap::getPalleteInfo(int index)
{
    index = (index < palletes_info.size())? index : 0;
    index = (index <0)? active : index;
    return palletes_info.at(index);
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
