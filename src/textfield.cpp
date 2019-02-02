#ifdef __linux__
    #include "include/textfield.h"
#else
    #include "textfield.h"
#endif


TextField::TextField()
    :prev_text("-1"),text(""), active(false)
{

}

TextField::TextField(std::string text, int x, int y, int w, int h, GuiHandler *handler, GuiDrawer *drawer)
{
    this->text = text;
    setPosition(x,y);
    setDimensions(w,h);
    setHandler(handler);
    setDrawer(drawer);
}

TextField::~TextField()
{

}

void TextField::update(GuiEvent *event)
{
    if(event->mouse_x > x && event->mouse_y > y &&  event->mouse_x < x+w && event->mouse_y < y+h)
    {
        if(event->mouse_pressed) active = true;
    }
    else if(event->mouse_pressed) active = false;


    if(active)
    {
        //printf("%i\n", (char)event->char_clicked );
        if(std::isprint(event->char_clicked))
        {
            text = text + (char)event->char_clicked;
        }
        else if (event->char_clicked == BACKSPACE) {
            text = text.substr(0,text.size()-1);
        }
        else if (event->char_clicked == ENTER) {
            if(handler) handler->handle(this);
        }
    }

    if(prev_text != text)
    {
        if(drawer) drawer->draw(this);
        prev_text = text;
    }
}
