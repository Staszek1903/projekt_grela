#include "include/button.h"

Button::Button()
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
        if(handler) handler->handle(this);
    }
}

void Button::draw()
{
    if(drawer) drawer->draw(this);
}
