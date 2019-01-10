#ifdef __linux__
    #include "include/algorytmy.h"
#else
    #include "algorytmy.h"
#endif

#include <iostream>

using namespace std;

void seeExceptions(EXCEPTION_CODE error)
{
    switch (error) {
    case EXCEPTION_CODE::openError:
        cerr << "Blad otwarcia pliku odczytu" << endl;
        break;
    case EXCEPTION_CODE::createError:
        cerr << "Blad tworzenia pliku zapisu" << endl;
        break;
    case EXCEPTION_CODE::alloc_problem:
        cerr << "Blad alokacji tablicy" << endl;
        break;
    default:
        cerr << "Nieznany blad";
        break;
    }
}


std::fstream OpenFile(std::string dir, std::ios_base::openmode base)
{
    std::fstream file(dir.c_str(), base);

    try
    {
        if (!file.is_open())
        {
            throw EXCEPTION_CODE::openError;
        }
    }

    catch (EXCEPTION_CODE error)
    {
        seeExceptions(error);

    }

    return file;
}

template <typename T>
void binaryWrite(std::fstream &file, T& value)
{
    int size = sizeof(T);
    void * pointer = (void *) &value;
    char * bytes = (char *) pointer;
    for(int i=0; i<size; ++i)
    {
        //printf("DEBUG: %i %c\n", bytes[i], (char)bytes[i]);
        file.put(bytes[i]);
    }
}

template <typename T>
void binaryRead(std::fstream & file, T& value)
{
    int size = sizeof(T);
    void * pointer = &value;
    char * bytes = (char *)pointer;
    for(int i=0; i<size; ++i)
        bytes[i] = file.get();
}

void write_to_okon(std::string dir, CompressedData& data, Pallete& paleta, TYPE_OF_PALLETE typeOfPallete, Bitmap& in)
{
    auto file = OpenFile(dir, std::ios::binary | std::ios::out);
    char format[] = "OKON";
    int width = in.getWidth();
    int height = in.getHeight();
    int size = data.getDataSize();
    Uint8 pallete_type = typeOfPallete;
    Uint8 * raw_data = data.getDataPointer();

    binaryWrite(file,format);
    binaryWrite(file,size);
    binaryWrite(file, width);
    binaryWrite(file,height);
    binaryWrite(file,pallete_type);
    if(typeOfPallete == DEDICATED)
    {
        for(int i=0 ;i<8; ++i)
            binaryWrite(file,paleta.c[i]);
    }

    for(int i=0; i<size; ++i)
        binaryRead(file, raw_data[i]);

    //printf("DEBUG: %i  %i  %i\n", size, width, height);
    file.close();
}

void read_from_okon(std::string dir, CompressedData &data)
{
    auto file = OpenFile(dir, std::ios::in|std::ios::binary);
    char format[5];
    int size, width, height;
    Uint8 pallete_type;
    Pallete pallete;
    auto & vector_data = data.getDataRef();


    binaryRead(file, format);
    binaryRead(file, size);
    binaryRead(file, width);
    binaryRead(file, height);
    binaryRead(file, pallete_type);
    if(pallete_type == DEDICATED)
    {
        for(int i=0 ;i<8; ++i)
            binaryRead(file, pallete.c[i]);
    }

    for(int i=0; i<size; ++i)
    {
        Uint8 byte;
        binaryRead(file,byte);
        vector_data.push_back(byte);
    }

    printf("OUTPUT DEBUG: %i  %i  %i %s\n", size, width, height, format);

    file.close();
}


void test5(Screen & screen)
{
    printf("PLIKI HEHEHEHEH\n");

    CompressedData data_out, data_in;
    Bitmap in("obrazek1.bmp");
    Pallete paleta;
    write_to_okon("test_file.okon", data_in , paleta, DEFAULT, in);

    read_from_okon("test_file.okon", data_out);
    printf("PLIKI END\n");
}

