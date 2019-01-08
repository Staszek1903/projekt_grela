
#include "Screen.h"
#include <vector>

struct CompressedData
{

    std::vector <Uint8> data;
    unsigned long bitSize;

    CompressedData() :data(1,0), bitSize(0){}
    CompressedData(CompressedData & other) : data(other.data), bitSize(other.bitSize){}
    CompressedData& operator= ( CompressedData& other) { data = other.data; bitSize = other.bitSize; return *this; }
    ~CompressedData(){}

    Uint8 * getDataPointer();
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

void to3bit(Bitmap &in, Bitmap &out);
void test4(Screen & screen);
