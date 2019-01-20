#ifndef TEXTFIELD_H
#define TEXTFIELD_H

#ifdef __linux__
    #include "include/guinode.h"
#else
    #include "guinode.h"
#endif

#include <string>


class TextField : public GuiNode
{
public:
    std::string prev_text;
    std::string text;
    bool active;

    TextField();
    TextField(std::string text, int x, int y, int w, int h, GuiHandler * handler, GuiDrawer * drawer);
    virtual ~TextField() override;
    virtual void update(GuiEvent *) override;
};

#endif // TEXTFIELD_H
