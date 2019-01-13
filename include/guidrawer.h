#ifndef GUIDRAWER_H
#define GUIDRAWER_H

class GuiNode;

class GuiDrawer
{
public:
    virtual void draw( GuiNode * node) =0;
    virtual ~GuiDrawer(){}
};

#endif // GUIDRAWER_H
