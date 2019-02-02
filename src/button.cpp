#ifdef __linux__
    #include "include/button.h"
#else
    #include "button.h"
#endif

Button::Button()
    :prev_state(-1),state(STAND_BUY)
{}

Button::Button(std::string name, int x, int y, int w, int h, GuiHandler *handler, GuiDrawer *drawer)
{
    setName(name);
    setPosition(x,y);
    setDimensions(w,h);
    setHandler(handler);
    setDrawer(drawer);
}

Button::~Button()
{
}

void Button::setName(std::string name)
{
    this->name = name;
}

std::string Button::getName()
{
    return  name;
}

void Button::update(GuiEvent *event)
{
    if(event->mouse_x > x && event->mouse_y > y &&  event->mouse_x < x+w && event->mouse_y < y+h)
    {
        //printf("state: %i\n", event->mouse_pressed);
        if(state != CLICKED) state = HAS_MOUSE;
        if(event->mouse_pressed) state = CLICKED;
        if(event->mouse_released && state == CLICKED)
        {
            state = HAS_MOUSE;
            if(handler) handler->handle(this);
        }
    }
    else
        state = STAND_BUY;


    if(prev_state != state)
    {
        if(drawer) drawer->draw(this);
        prev_state = state;
    }
}
