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

#include "guipallete.h"
#include "button.h"

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
    GuiPallete &guipallete;
    SaveOkonHandler(TextField &filename, GuiBitmap &bitmap, GuiPallete &pallete);
    virtual void handle(GuiNode *) override;
};

class PaleteUpHandler: public GuiHandler
{
public:
    GuiPallete & guipallete;
    PaleteUpHandler(GuiPallete & pallete);
    virtual void handle(GuiNode *) override;
};

class PaleteDownHandler: public GuiHandler
{
public:
    GuiPallete & guipallete;
    PaleteDownHandler(GuiPallete & pallete);
    virtual void handle(GuiNode *) override;
};

class PaleteGenerateHandler: public GuiHandler
{
public:
    GuiPallete & guipallete;
    GuiBitmap & bitmap;
    PaleteGenerateHandler(GuiPallete & pallete, GuiBitmap & bitmap);
    virtual void handle(GuiNode *) override;
};

class Bit3Handler: public GuiHandler
{
public:
    GuiPallete & guipallete;
    GuiBitmap & bitmap;
    Bit3Handler(GuiPallete & pallete, GuiBitmap & bitmap);
    virtual void handle(GuiNode *) override;
};

class Bit3DitterHandler: public GuiHandler
{
public:
    GuiPallete & guipallete;
    GuiBitmap & bitmap;
    Bit3DitterHandler(GuiPallete & pallete, GuiBitmap & bitmap);
    virtual void handle(GuiNode *) override;
};

class OriginalHandler: public GuiHandler
{
public:
    GuiPallete & guipallete;
    GuiBitmap & bitmap;
    OriginalHandler(GuiPallete & pallete, GuiBitmap & bitmap);
    virtual void handle(GuiNode *) override;
};

#endif // HANDLERS_H
