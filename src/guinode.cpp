#include "include/guinode.h"

GuiNode::GuiNode()
    :handler(nullptr), drawer(nullptr),x(0),y(0),w(0),h(0){};

GuiNode::~GuiNode()
{
    if(handler) delete handler;
    if(drawer) delete drawer;
}

void GuiNode::setPosition(int x, int y)
{
    this->x = x;
    this->y = y;
}

void GuiNode::setDimensions(int w, int h)
{
    this->w = w;
    this->h = h;
}

void GuiNode::setHandler(GuiHandler * handler)
{
    this->handler = handler;
}

void GuiNode::setDrawer(GuiDrawer *drawer)
{
    this->drawer = drawer;
}
