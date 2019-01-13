#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#ifdef __linux__
    #include "include/guinode.h"
#else
    #include "button.h"
#endif

class Button : public GuiNode
{
    std::string name;
public:
    Button();
    virtual ~Button() override;
    void setName(std::string name);
    virtual void update(GuiEvent * event) override;
    virtual void draw() override;
};

#endif // BUTTON_H
