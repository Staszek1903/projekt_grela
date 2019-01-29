#ifdef __linux__
    #include "include/handlers.h"
#else
    #include "handlers.h"
#endif

OpenBmpHandler::OpenBmpHandler(TextField &filename, GuiBitmap &bitmap)
    :filename(filename), bitmap(bitmap)
{}

void OpenBmpHandler::handle(GuiNode *)
{
    //printf("opening: %s\n", filename.text.c_str());



    auto & temp = bitmap.addBitmap(Bitmap(filename.text),ORIGINAL);

    if(!temp.isCreated())
    {
        filename.text = filename.text + "BAD";
        //printf("canot open\n");
    }
    else
    {
        filename.text = "LOADED";
        bitmap.draw();
    }
    filename.draw();
}

SaveBmpHandler::SaveBmpHandler(TextField &filename, GuiBitmap &bitmap)
    :filename(filename), bitmap(bitmap)
{}

void SaveBmpHandler::handle(GuiNode *)
{
    printf("saving: %s\n",filename.text.c_str());

    auto & temp = bitmap.getBitmap(-1);
    if(temp.saveBMP(filename.text))
    {
        filename.text = "SAVED";
    }
    else
    {
        filename.text += "BAD";
    }

    filename.draw();
}

OpenOkonHandler::OpenOkonHandler(TextField &filename, GuiBitmap &bitmap)
    :filename(filename), bitmap(bitmap)
{}

void OpenOkonHandler::handle(GuiNode *)
{
    CompressedData data;
    Bit3BMP bit3;
    if(!read_from_okon(filename.text, data))
    {
        filename.text += "BAD";
        filename.draw();
        return;
    }
    else
    {
        filename.text = "LOADED";
        filename.draw();
    }

    Bitmap bmp;
    dekompression(bit3,data);
    bit3toBitmap(bit3,bmp);

    bitmap.addBitmap(bmp,0);
    bitmap.draw();
}

SaveOkonHandler::SaveOkonHandler(TextField &filename, GuiBitmap &bitmap, GuiPallete &pallete)
    :filename(filename), bitmap(bitmap), guipallete(pallete)
{}

void SaveOkonHandler::handle(GuiNode *)
{
     auto & current = bitmap.getBitmap(-1);
     Bit3BMP bit3= to3bitTab(current,guipallete.getActivePallete());
     std::string dir = filename.text;

     CompressedData data;
     compression(data, bit3);

     if(write_to_okon(dir, data))
     {
         filename.text = "SAVED";
     }
     else
     {
         filename.text += "DIR";
     }

     filename.draw();
}

PaleteUpHandler::PaleteUpHandler(GuiPallete &pallete)
    :guipallete(pallete)
{
}

void PaleteUpHandler::handle(GuiNode *)
{
    guipallete.setActive(guipallete.getActive()+1);
    printf("up");
}

PaleteDownHandler::PaleteDownHandler(GuiPallete &pallete)
    :guipallete(pallete)
{
}

void PaleteDownHandler::handle(GuiNode *)
{
    printf("down");
    guipallete.setActive(guipallete.getActive()-1);
}

PaleteGenerateHandler::PaleteGenerateHandler(GuiPallete &pallete, GuiBitmap &bitmap)
    :guipallete(pallete), bitmap(bitmap)
{
}

void PaleteGenerateHandler::handle(GuiNode * me)
{
   auto m = (Button *) me;
   m->setName("GENERATING");
   m->draw();
   auto & current = bitmap.getBitmap(-1);
    if(current.isCreated())
    {
        Pallete dedicated = getPallete(current);
        dedicated = Reorder(dedicated,current);

        guipallete.setGeneratedPalete(dedicated);
    }

    m->setName("GENERATE");
    m->draw();
}

Bit3Handler::Bit3Handler(GuiPallete &pallete, GuiBitmap &bitmap)
    :guipallete(pallete), bitmap(bitmap)
{
}

void Bit3Handler::handle(GuiNode *)
{
    auto & current = bitmap.getBitmap(-1);
    Pallete pallet = guipallete.getActivePallete();
    Bitmap out;
    to3bitBMP(current,out,pallet);

    bitmap.addBitmap(out,0);
}

Bit3DitterHandler::Bit3DitterHandler(GuiPallete &pallete, GuiBitmap &bitmap)
:guipallete(pallete), bitmap(bitmap)
{
}

void Bit3DitterHandler::handle(GuiNode *)
{
    auto & current = bitmap.getBitmap(-1);
    Pallete pallet = guipallete.getActivePallete();
    Bitmap out = current;
    dittering(out,pallet);
    bitmap.addBitmap(out,0);
}

OriginalHandler::OriginalHandler(GuiPallete &pallete, GuiBitmap &bitmap)
:guipallete(pallete), bitmap(bitmap)
{
}

void OriginalHandler::handle(GuiNode *)
{
    bitmap.setActive(0);
}
