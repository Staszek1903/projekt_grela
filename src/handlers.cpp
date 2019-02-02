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



    auto & temp = bitmap.setOiginal(Bitmap(filename.text));

    if(!temp.isCreated())
    {
        filename.text = filename.text + "BAD";
        printf("canot open\n");
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

    auto & temp = bitmap.getActive();
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

    bitmap.set3bit(bmp,bit3.paleta);
    bitmap.draw();
}

SaveOkonHandler::SaveOkonHandler(TextField &filename, GuiBitmap &bitmap, GuiPallete &pallete)
    :filename(filename), bitmap(bitmap), guipallete(pallete)
{}

void SaveOkonHandler::handle(GuiNode *)
{
     auto & current = bitmap.get3bit();
     if(!current.isCreated()) return;

     Pallete current_pallete = bitmap.getPallete();

     Bitmap bitmapa(160,20);
         for(int i = 0; i < 8; i++)
             for(int j = 0; j < 20; j++)
                 for(int k = 0; k < 20; k++)
             bitmapa.setPixel(k+i*20,j,current_pallete.c[i]);
         bitmap.set3bit(bitmapa,current_pallete);
         bitmap.draw();


     Bit3BMP bit3= to3bitTab(current,current_pallete);
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
   auto & current = bitmap.getOriginal();
    if(current.isCreated())
    {
        Pallete dedicated = getPallete(current);
        dedicated = Reorder(dedicated,current);

        guipallete.setGeneratedPalete(dedicated);               /////////
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
    auto & current = bitmap.getOriginal();
    Pallete pallet = guipallete.getActivePallete();
    Bitmap out;
    to3bitBMP(current,out,pallet);

    bitmap.set3bit(out, pallet);
}

Bit3DitterHandler::Bit3DitterHandler(GuiPallete &pallete, GuiBitmap &bitmap)
:guipallete(pallete), bitmap(bitmap)
{
}

void Bit3DitterHandler::handle(GuiNode *)
{
    auto & current = bitmap.getOriginal();
    if(!current.isCreated()) return;

    Pallete pallet = guipallete.getActivePallete();
    Bitmap out = current;
    dittering(out,pallet);
    bitmap.set3bit(out, pallet);
}

OriginalHandler::OriginalHandler(GuiPallete &pallete, GuiBitmap &bitmap)
:guipallete(pallete), bitmap(bitmap)
{
}

void OriginalHandler::handle(GuiNode *)
{
    bitmap.setActive(0);
}
