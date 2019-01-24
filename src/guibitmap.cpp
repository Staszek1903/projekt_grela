#ifdef __linux__
    #include "include/guibitmap.h"
#else
    #include "guibitmap.h"
#endif


GuiBitmap::GuiBitmap(int x, int y, Screen &screen)
    :screen(screen)
{
    this->x = x;
    this->y = y;
}

void GuiBitmap::update(GuiEvent *)
{

}

void GuiBitmap::draw()
{
    screen.draw(surface,x,y);
}
