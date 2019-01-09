#ifdef __linux__
    #include <SDL/SDL.h>
#else
    #include <SDL.h>
#endif

#include "Screen.h"
#include <vector>

class CompressedData
{

    std::vector <Uint8> data;
    unsigned long bitSize;

public:
    CompressedData() :data(1,0), bitSize(0){}
    CompressedData(CompressedData & other) : data(other.data), bitSize(other.bitSize){}
    CompressedData& operator= ( CompressedData& other) { data = other.data; bitSize = other.bitSize; return *this; }
    ~CompressedData(){}

    Uint8 * getDataPointer();
    std::vector<Uint8>& getDataRef();
    void dataResize(int size);
    int getDataSize();
    unsigned long getBitSize();
    void setBitSize(unsigned long);

    void writeBit(Uint8 bit);
    Uint8 readBit();
    void printData();
    void encodeByte(Uint8 byte, int k);
    Uint8 decodeByte(int k);
};


struct Bit3BMP
{
    std::vector <Uint8> data;
};

struct Pallete
{
    SDL_Color c[8];
};

void compression(CompressedData &out, Bit3BMP &in );
void dekompression (Bit3BMP & out, CompressedData & in);
void test1(Screen & screen);

void dittering(Bitmap & in, Bitmap & out, Pallete paleta);
void test2(Screen & screen);

Pallete getPallete(Bitmap & in);
void test3(Screen & screen);

void to3bitBMP(Bitmap &in, Bitmap &out, Pallete paleta);
Bit3BMP to3bitTab(Bitmap &in, Pallete paleta);
void test4(Screen & screen);
