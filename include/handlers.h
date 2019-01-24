#ifndef HANDLERS_H
#define HANDLERS_H

#ifdef __linux__
    #include "include/guihandler.h"
    #include "include/guibitmap.h"
    #include "include/textfield.h"
    #include "include/algorytmy.h"
#else
    #include "guibitmap.h"
    #include "guihandler.h"
    #include "textfield.h"
    #include "algorytmy.h"
#endif

class OpenBmpHandler: public GuiHandler
{
public:
    TextField & filename;
    GuiBitmap & bitmap;
    OpenBmpHandler(TextField &filename, GuiBitmap &bitmap);
    virtual void handle(GuiNode *) override;
};

class SaveBmpHandler: public GuiHandler
{
public:
    TextField & filename;
    GuiBitmap & bitmap;
    SaveBmpHandler(TextField &filename, GuiBitmap &bitmap);
    virtual void handle(GuiNode *) override;
};

class OpenOkonHandler: public GuiHandler
{
public:
    TextField & filename;
    GuiBitmap & bitmap;
    OpenOkonHandler(TextField &filename, GuiBitmap &bitmap);
    virtual void handle(GuiNode *) override;
};

class SaveOkonHandler: public GuiHandler
{
public:
    TextField & filename;
    GuiBitmap & bitmap;
    SaveOkonHandler(TextField &filename, GuiBitmap &bitmap);
    virtual void handle(GuiNode *) override;
};
#endif // HANDLERS_H
