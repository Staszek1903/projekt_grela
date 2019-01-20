#ifdef __linux__
    #include "include/sdltextfield.h"
#else
    #include "sdltextfield.h"
#endif

TexFieldDrawer::TexFieldDrawer(Screen &screen, SDL_Color color)
    :screen(&screen), field(nullptr), color(color), font(nullptr)
{
}

TexFieldDrawer::~TexFieldDrawer()
{
    if(field) delete field;
}

void TexFieldDrawer::draw(GuiNode * node)
{
    TextField * tf = static_cast<TextField *>(node);
    if(!font) loadFont();
    if(!field) createField(tf->text, tf->w,tf->h);

    createField(tf->text,tf->w,tf->h);
    screen->draw(*field,tf->x,tf->y);
}

void TexFieldDrawer::createField(std::string text, int w, int h)
{
    if(field) delete field;
    field = new Bitmap(w, h);

    for(int i=0; i<w; ++i)
        for(int j=0; j<h; ++j)
            if(i<5 || i>w-5 || j<5 || j>h-5)
                field->setPixel(i,j,{color.r<<1,color.g<<1,color.b<<1});
            else
                field->setPixel(i,j,color);

    if(text.size() != 0)
    {
        SDL_Surface * t = TTF_RenderText_Solid(font,text.c_str(),{0,0,0});
        field->draw(t,5,5);
    }
}

void TexFieldDrawer::loadFont()
{
    font = TTF_OpenFont("font.ttf", 32);
}

