#ifndef ALGORYTMY_H_
#define ALGORYTMY_H_


#ifdef __linux__
    #include <SDL/SDL.h>
#else
    #include <SDL.h>
#endif

#include "Screen.h"
#include <vector>
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

enum EXCEPTION_CODE
{
    openError,
    createError,
    alloc_problem
};

enum TYPE_OF_PALLETE
{
    DEFAULT,
    DEDICATED,
    GRAY_SCALE,
};

struct Pallete
{
    SDL_Color c[8];
};

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
    int getOriginalDataSize();
    void setOriginalDataSize();
    unsigned long getBitSize();
    void setBitSize(unsigned long);

    void writeBit(Uint8 bit);
    Uint8 readBit();
    void printData();
    void encodeByte(Uint8 byte, int k);
    Uint8 decodeByte(int k);
public:
    int original_width;
    int original_height;
    Pallete palete;
    TYPE_OF_PALLETE palete_type;
};

struct Bit3BMP
{
    std::vector <Uint8> data;
    int width;
    int height;
    TYPE_OF_PALLETE palete_type;
    Pallete paleta;
};

Pallete NarzuconaPaleta();

Pallete SkalaSzarosci();

void compression(CompressedData &out, Bit3BMP &in );
void dekompression (Bit3BMP & out, CompressedData & in);
void test1(Screen & screen);

void dittering(Bitmap & in, Pallete paleta);
void test2(Screen & screen);

bool sortCompRed(SDL_Color i, SDL_Color j);
bool sortCompGreen(SDL_Color i, SDL_Color j);
bool sortCompBlue(SDL_Color i, SDL_Color j);
int vectorIncludes(vector<SDL_Color> tab, SDL_Color col);
SDL_Color averageColor(vector<SDL_Color> tab, int min, int max);

Pallete getPallete(Bitmap & in);
void test3(Screen & screen);

Pallete Reorder(Pallete paleta, Bitmap &in);
Pallete NarzuconaPaleta();
Pallete SkalaSzarosci();
Pallete SkalaSzarosci(Pallete paleta);
SDL_Color FindColor(SDL_Color pixel, Pallete paleta);
int FindIndex(SDL_Color pixel, Pallete paleta);
void to3bitBMP(Bitmap &in, Bitmap &out, Pallete paleta);
Bit3BMP to3bitTab(Bitmap &in, Pallete paleta);
void bit3toBitmap(Bit3BMP & in, Bitmap &out);

void test4(Screen & screen);

void seeExceptions(EXCEPTION_CODE error);

bool write_to_okon(std::string dir, CompressedData& data);
bool read_from_okon(std::string dir, CompressedData &data);

void test5(Screen & screen);


#endif /* ALGORYTMY_H_ */
