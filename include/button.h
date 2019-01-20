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
    Button(std::string name, int x, int y, int w, int h, GuiHandler* handler, GuiDrawer * drawer);
    virtual ~Button() override;
    void setName(std::string name);
    std::string getName();
    virtual void update(GuiEvent * event) override;

    int prev_state;
    int state;
    enum{
        STAND_BUY,
        HAS_MOUSE,
        CLICKED
    };
};

#endif // BUTTON_H
