#ifndef BITMAP_H
#define BITMAP_H

#ifdef __linux__
    #include <SDL/SDL.h>
#else
    #include <SDL.h>
#endif

#include <string>


/**
* Klasa do przechowywania i operacji na obrazie
*/
class Bitmap
{
public:

    Bitmap();
    /**
    * Bitmap(int,int) tworzy pusty obraz o wymiarach w na h
    */
    Bitmap(int width, int height);
    /**
    * Bitmap(string) ³aduje plik BMP ze œciezki dir
    */
    Bitmap(std::string dir);

    /**
     * @brief Konstruktor kopiuj?cy
     */
    Bitmap(const Bitmap &);

    /**
     * @brief Operator kopiowania
     * @return refka na t? bitmape
     */
    Bitmap& operator= (const Bitmap &);

    virtual ~Bitmap();

    /**
    * rysowanie obrazu na screen w miejscu x,y
    */
    void draw(SDL_Surface * screen, int x, int y);
    /**
     * @brief rysuje inn? bitmape na tej bitmapie w mijscu x,y
     * @param other - bitmapa do narysowania
     * @param x
     * @param y
     */
    void draw(const Bitmap &other, int x, int y);

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
    int getWidth() const;
    int getHeight() const;
    bool isCreated();

    void loadBMP(std::string dir);
    void create(int x,int y);

protected:
    SDL_Surface * surface;
};

#endif // BITMAP_H
