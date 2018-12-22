
#include "Screen.h"

struct CompressedData
{
    Uint8 * data;
    int size;

    CompressedData() :data(nullptr), size(0){}
    CompressedData(CompressedData & other) : data(other.data), size(other.size) {other.data = nullptr; other.size = 0;}
    ~CompressedData() { if(data) delete [] data; }
};

struct Pallete
{
    SDL_Color c[8];
};

CompressedData compression( Bitmap & obraz);
void dekompression (Bitmap & out, CompressedData & in);
void test1(Screen & screen);

void dittering(Bitmap & in, Bitmap & out, Pallete paleta);
void test2(Screen & screen);

Pallete getPallete(Bitmap & in);
void test3(Screen & screen);

void to3bit(Bitmap &in, Bitmap &out);
void test4(Screen & screen);
