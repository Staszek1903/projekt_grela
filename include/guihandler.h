#ifndef GUIHANDLER_H
#define GUIHANDLER_H

class GuiNode;

class GuiHandler
{
public:
    virtual void handle(GuiNode * node) = 0;
    virtual ~GuiHandler(){}
};

#endif // GUIHANDLER_H
