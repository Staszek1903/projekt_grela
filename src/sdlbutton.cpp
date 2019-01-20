#ifdef __linux__
    #include "include/sdlbutton.h"
#else
    #include "sdlbutton.h"
#endif

ButtonDrawer::ButtonDrawer(Screen & screen, SDL_Color color)
    :screen(&screen), color(color), text(nullptr), stand_by(nullptr), has_mouse(nullptr), clicked(nullptr)
{

}

ButtonDrawer::~ButtonDrawer()
{
    if(stand_by) delete stand_by;
    if(has_mouse) delete has_mouse;
    if(clicked) delete clicked;
    if(text) SDL_FreeSurface(text);
}

void ButtonDrawer::draw(GuiNode * node)
{
    Button * b = static_cast<Button *>(node);
    Bitmap temp(b->w, b->h);

    if(!text) createText(b->getName());
    if(!stand_by) createStandBy(b->w,b->h);
    if(!has_mouse) createHasMouse(b->w,b->h);
    if(!clicked) createCLicked(b->w,b->h);

    if(b->state == Button::STAND_BUY)
        screen->draw(*stand_by,b->x,b->y);
    else if(b->state == Button::HAS_MOUSE)
        screen->draw(*has_mouse,b->x,b->y);
    else if(b->state == Button::CLICKED)
        screen->draw(*clicked,b->x,b->y);
}

void ButtonDrawer::createText(std::string ctext)
{
    TTF_Font *font = TTF_OpenFont("font.ttf",32);
    if(!font)
        {printf("UNABLE TO LOAD FONT\n"); return;}

    text = TTF_RenderText_Solid(font, ctext.c_str(),{0,0,0});
    if(!text)
        printf("UNABLE TO CREATE TEXT\n");

    TTF_CloseFont(font);
}

void ButtonDrawer::createStandBy(int w, int h)
{
    //printf("CREATINF SB\n");
    stand_by = new Bitmap(w,h);
    for(int i=0; i <w; ++i)
        for(int j=0; j <h; ++j)
            if(i<5 || i>w-5 || j<5 || j>h-5)
                stand_by->setPixel(i,j,{(color.r>>2),(color.g>>2),(color.b>>2)});
            else
                stand_by->setPixel(i,j,color);
    stand_by->draw(text,5,5);
}

void ButtonDrawer::createHasMouse(int w, int h)
{
    has_mouse = new Bitmap(w,h);
    for(int i=0; i <w; ++i)
        for(int j=0; j <h; ++j)
        {
            float x = (w)/2;
            float y = (h)/2;
            float r_max = std::sqrt(x*x+y*y);
            float rx = x-i, ry = y-j;
            float r = std::sqrt(rx*rx+ry*ry);
            float q = r/r_max;
            //printf("r_max = %f x: %f  y: %f\n",q, x,y);
            if(i<5 || i>w-5 || j<5 || j>h-5)
                has_mouse->setPixel(i,j,{(color.r>>2),(color.g>>2),(color.b>>2)});
            else
                has_mouse->setPixel(i,j,{(color.r*q),(color.g*q),(color.b*q)});
        }

    has_mouse->draw(text,5,5);
}

void ButtonDrawer::createCLicked(int w, int h)
{
    clicked = new Bitmap(w,h);
    for(int i=0; i <w; ++i)
        for(int j=0; j <h; ++j)
            clicked->setPixel(i,j,{(color.r>>2),(color.g>>2),(color.b>>2)});
    clicked->draw(text,5,5);
}

void ButtonHandler::handle(GuiNode * node)
{
    printf("button pressed: %i %i\n", node->x, node->y);
}
