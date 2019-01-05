#include "include/algorytmy.h"

CompressedData compression( Bitmap & obraz)
{
    CompressedData ret;
    return ret;
}

void dekompression (Bitmap & out, CompressedData & in)
{

}

void test1(Screen & screen)
{
    Bitmap a("obrazek4.bmp");

    for(int i=0;i<200; ++i)
    {
        for(int j=0; j<200; ++j)
        a.setPixel(i,j,{200,0,0});
    }

    screen.draw(a,0,0);

    printf("test1\n");
}
