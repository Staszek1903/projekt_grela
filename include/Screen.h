#ifndef SCREEN_H
#define SCREEN_H

#include "Bitmap.h"


/**
* Klasa okna
*/

class Screen : public Bitmap
{
public:
    /**
    * Tworzy okno o wymiarach width na height o nazwie name
    */
    Screen(int width, int height, std::string name);
    virtual ~Screen();

    Screen(const Screen &) = delete;
    Screen& operator= (const Screen&) = delete;

    /**
    * zamiana bufora
    */
    void flip();

    /**
    * rysuje bitmape w oknie w miejscu x,y
    */
    void draw(Bitmap &bitmap, int x, int y);
};

#endif // SCREEN_H
