#ifndef GUINODE_H
#define GUINODE_H

#ifdef __linux__
    #include "include/guihandler.h"
    #include "include/guievent.h"
    #include "include/guidrawer.h"
#else
    #include "guihandler.h"
    #include "guievent.h"
    #include "guidrawer.h"
#endif

class GuiNode
{
protected:

    GuiHandler * handler;
    GuiDrawer * drawer;
public:
    int x, y, w, h;


    GuiNode();
    virtual ~GuiNode();

    void setPosition(int x, int y);
    void setDimensions(int w, int h);
    void setHandler( GuiHandler * handler );
    void setDrawer( GuiDrawer * drawer);
    virtual void update( GuiEvent * event ) =0;
    virtual void draw();
};

#endif // GUINODE_H
