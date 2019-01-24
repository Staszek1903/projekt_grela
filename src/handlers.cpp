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

    bitmap.loadBMP(filename.text);

    if(!bitmap.isCreated())
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

    if(bitmap.saveBMP(filename.text))
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

    dekompression(bit3,data);
    bit3toBitmap(bit3,bitmap);

    bitmap.draw();
}

SaveOkonHandler::SaveOkonHandler(TextField &filename, GuiBitmap &bitmap)
    :filename(filename), bitmap(bitmap)
{}

void SaveOkonHandler::handle(GuiNode *)
{

}
