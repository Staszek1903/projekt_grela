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

bool write_to_okon(std::string dir, CompressedData& data)
{
    auto file = OpenFile(dir, std::ios::binary | std::ios::out);
    if(!file.good()) return  false;
    char format[] = "OKON";
    int width = data.original_width;
    int height = data.original_height;
    int size = data.getDataSize();
    Uint8 typeOfPallete = data.palete_type;
    Uint8 * raw_data = data.getDataPointer();
    Pallete paleta = data.palete;


    binaryWrite(file,format);
    binaryWrite(file,size);
    binaryWrite(file, width);
    binaryWrite(file,height);
    binaryWrite(file,typeOfPallete);

    if(typeOfPallete == DEDICATED)
    {
        for(int i=0 ;i<8; ++i)
            binaryWrite(file,paleta.c[i]);
    }

    for(int i=0; i<size; ++i)
        binaryWrite(file, raw_data[i]);

    //printf("DEBUG: %i  %i  %i\n", size, width, height);
    file.close();

    return true;
}

bool read_from_okon(std::string dir, CompressedData &data)
{
    auto file = OpenFile(dir, std::ios::in|std::ios::binary);
    if(!file.good()) return false;

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

    printf("pallete type: %i" , pallete_type);

    switch(pallete_type)
    {
        case DEDICATED:
            printf("<<<<<<<<<DEDYKOWANA\n");
            for(int i=0 ;i<8; ++i)
                binaryRead(file, pallete.c[i]);
        break;

        case DEFAULT:
            printf("<<<<<<<<<nazucona\n");
            pallete = NarzuconaPaleta();
        break;

        case GRAY_SCALE:
            printf("<<<<<<<<<SKALA SZAROSCI\n");
            pallete = SkalaSzarosci();
        break;

    }

    vector_data.clear();
    for(int i=0; i<size; ++i)
    {
        Uint8 byte;
        binaryRead(file,byte);
        vector_data.push_back(byte);
    }

    data.original_width = width;
    data.original_height = height;
    data.palete_type = (TYPE_OF_PALLETE) pallete_type;
    data.palete = pallete;

   // printf("OUTPUT DEBUG: %i  %i  %i %s\n", size, width, height, format);

    file.close();
    return true;
}

template <typename T>
void compare_bytewise(T& a, T&b)
{
    int size = sizeof(T);
    void * va = (void*)&a;
    void * vb = (void*)&b;
    Uint8 * ia = (Uint8*)va;
    Uint8 * ib = (Uint8*)vb;

    for(int i=0; i<size; ++i)
    {
        printf("%i) a: %i b: %i",i, ia[i], ib[i]);
        if(ia[i] != ib[i])
            printf(" <<<<<<<<<<<<<< NOT GOOD\n");
        else
            printf("\n");
    }
}


void test5(Screen & screen)
{
    printf("PLIKI HEHEHEHEH\n");

    Bitmap bmp_original("obrazek2.bmp"),
            bmp_altered, bmp_out;
    Pallete pallete = NarzuconaPaleta();
    Bit3BMP data_in, data_out;
    CompressedData compressed_in, compressed_out;
    compressed_in.palete_type = compressed_out.palete_type = TYPE_OF_PALLETE::DEFAULT;

    bmp_altered = bmp_original;
    dittering(bmp_altered,pallete);
    //to3bitBMP(bmp_original, bmp_altered, pallete);

    screen.draw(bmp_original,0,0);
    screen.draw(bmp_altered,bmp_original.getWidth(),0);

    data_in = to3bitTab(bmp_altered,pallete);
    printf("Bit3 size: %i\n", data_in.data.size());

    compression(compressed_in,data_in);
    printf("compressed size: %i\n", compressed_in.getDataSize());


    std::string file_name = "test_file.okon";
    write_to_okon(file_name, compressed_in);

    read_from_okon(file_name, compressed_out);

    dekompression(data_out,compressed_out);
    printf("dekompressed size: %i\n", data_out.data.size());


    auto & data1 = compressed_in.getDataRef();
    auto & data2 = compressed_out.getDataRef();
    for(int i=0; i<100; ++i)
    {
        if(data1.at(i) != data2.at(i))
            printf("%i) in: %i out: %i <<<<<<<<<<<<<<<< SHIEEET \n",i,data1.at(i), data2.at(i) );
    }

    printf("comp width %i %i\n", compressed_in.original_width, compressed_out.original_width);
    printf("comp heaight %i %i\n", compressed_in.original_height, compressed_out.original_height);
    printf("width %i %i\n", data_in.width, data_out.width);
    printf("height %i %i\n", data_out.height, data_out.height);

    bit3toBitmap(data_out,bmp_out);
    screen.draw(bmp_out,0,bmp_original.getHeight());


    printf("PLIKI END\n");

    //compare_bytewise(data_in,data_out);
    compare_bytewise(compressed_in.palete, compressed_out.palete);
}

