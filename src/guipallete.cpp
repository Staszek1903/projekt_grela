#ifdef __linux__
    #include "include/guipallete.h"
#else
    #include "guipallete.h"
#endif


GuiPallete::GuiPallete(Screen &screen, int x, int y)
    :screen(screen),active(0)
{
    this->x = x;
    this->y = y;
    palety[0] = NarzuconaPaleta();
    palety[1] = SkalaSzarosci();
}

void GuiPallete::setGeneratedPalete(Pallete p)
{
    palety[2] = p;
    palety[3] = SkalaSzarosci(p);
    setted = true;


    printf("redrawwww !!!!!!!");
    draw();
}

int GuiPallete::getActive()
{
    return active;
}

void GuiPallete::setActive(int active)
{
    if(setted && active>3)
        this->active = 0;
    else if (!setted && active>1)
        this->active = 0;
    else if (active < 0 && setted)
        this->active = 3;
    else if (active<0 && !setted)
        this->active = 1;
    else
        this->active = active;

    printf("\n%i %i\n", this->active, active);

    draw();
}

Pallete GuiPallete::getActivePallete()
{
    return palety[active];
}

TYPE_OF_PALLETE GuiPallete::getActivePalleteType()
{
    TYPE_OF_PALLETE type[4] = {DEFAULT,GRAY_SCALE,DEDICATED,DEDICATED};

    return type[active];
}

void GuiPallete::update(GuiEvent *)
{

}

void drawRect(int x,int y, int w, int h, SDL_Color color, Screen & screen,bool setted)
{
    for ( int i=x; i<x+w; ++i)
        for( int j=y; j<y+h; ++j)
            if(setted && (i<x+5||i>x+w-5||j<y+5||j>y+h-5))
                screen.setPixel(i,j,{color.r/2,color.g/2,color.b/2});
            else
                screen.setPixel(i,j,color);
}

void GuiPallete::draw()
{
    int size = (setted)? 4:2;

    for(int j=0; j<size; ++j)
        for( int i=0; i<8; ++i)
        {
            drawRect(x+i*50,y+j*55,50,50, palety[j].c[i], screen, (j==active));
        }
}
