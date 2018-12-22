#ifndef BITMAP_H
#define BITMAP_H

#include <SDL.h>
#include <string>


/**
* Klasa do przechowywania i operacji na obrazie
*/
class Bitmap
{
public:
    /**
    * Bitmap(int,int) tworzy pusty obraz o wymiarach w na h
    */
    Bitmap(int width, int height);
    /**
    * Bitmap(string) ³aduje plik BMP ze œciezki dir
    */
    Bitmap(std::string dir);

    Bitmap(const Bitmap &) = delete;
    Bitmap& operator= (const Bitmap &) = delete;

    virtual ~Bitmap();

    /**
    * rysowanie obrazu na screen w miejscu x,y
    */
    void draw(SDL_Surface * screen, int x, int y);
    /**
    * czysci ca³¹ bitmape na kolor color
    */
    void clear(SDL_Color color);
    /**
    * koloruje pixel x,y na kolor color
    */
    void setPixel(int x, int y, SDL_Color color);
    /**
    * pobiera dane na temat pixela x,y
    * @return SDL_Color kolor pixela
    */
    SDL_Color getPixel(int x, int y);

    /**
    * zwracaj¹ szerokoœci i wysokoœæ bitmapy w pixelach
    */
    int getWidth();
    int getHeight();

protected:
    SDL_Surface * surface;

    Bitmap();
    void loadBMP(std::string dir);
    void create(int x,int y);
};

#endif // BITMAP_H
