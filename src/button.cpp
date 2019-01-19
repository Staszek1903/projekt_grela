#include "include/button.h"

Button::Button()
    :state(STAND_BUY)
{}

Button::~Button()
{
    //GuiNode::~GuiNode();
}

void Button::setName(std::string name)
{
    this->name = name;
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
}

void Button::draw()
{
    if(drawer) drawer->draw(this);
}
