#ifdef __linux__
    #include "include/algorytmy.h"
#else
    #include "algorytmy.h"
#endif

#include <math.h>

// GENERACJA STRUKTURY Bit3BMP

void dittering(Bitmap & in, Pallete paleta)
{
   int width = in.getWidth();
   int height = in.getHeight();

   for(int y = 0 ; y < height ; y++ )
   {
        for(int x = 0 ; x < width ; x++ )
        {
            SDL_Color pix = in.getPixel(x,y);

            float oldR = pix.r;
            float oldG = pix.g;
            float oldB = pix.b;

            SDL_Color c_found = FindColor(in.getPixel(x,y), paleta);

            int newR = c_found.r;
            int newG = c_found.g;
            int newB = c_found.b;

            in.setPixel(x,y,c_found);

            float errR = oldR - newR;
            float errG = oldG - newG;
            float errB = oldB - newB;


            SDL_Color pix_1 = in.getPixel(x + 1, y);
            float r = pix_1.r;
            float g = pix_1.g;
            float b = pix_1.b;
            r = r + errR * 7/16.0;
            g = g + errG * 7/16.0;
            b = b + errB * 7/16.0;
            pix_1.r = r;
            pix_1.g = g;
            pix_1.b = b;
            in.setPixel(x + 1, y,pix_1);

            SDL_Color pix_2 = in.getPixel(x - 1, y + 1);
            r = pix_2.r;
            g = pix_2.g;
            b = pix_2.b;
            r = r + errR * 3/16.0;
            g = g + errG * 3/16.0;
            b = b + errB * 3/16.0;
            pix_2.r = r;
            pix_2.g = g;
            pix_2.b = b;
            in.setPixel(x - 1, y + 1,pix_2);

            SDL_Color pix_3 = in.getPixel(x , y + 1);
            r = pix_3.r;
            g = pix_3.g;
            b = pix_3.b;
            r = r + errR * 5/16.0;
            g = g + errG * 5/16.0;
            b = b + errB * 5/16.0;
            pix_3.r = r;
            pix_3.g = g;
            pix_3.b = b;
            in.setPixel(x , y + 1,pix_3);

            SDL_Color pix_4 = in.getPixel(x + 1, y + 1);
            r = pix_4.r;
            g = pix_4.g;
            b = pix_4.b;
            r = r + errR * 1/16.0;
            g = g + errG * 1/16.0;
            b = b + errB * 1/16.0;
            pix_4.r = r;
            pix_4.g = g;
            pix_4.b = b;
            in.setPixel(x + 1, y + 1,pix_4);

        }

   }
}

void test2(Screen & screen)
{
   Bitmap bmp1("obrazek2.bmp");
   Bitmap bmp2("obrazek2.bmp");
   Bitmap bmp3("obrazek2.bmp");
   Bitmap bmp4("obrazek2.bmp");
   Bitmap bmp11(bmp1.getWidth(),bmp1.getHeight());
   Bitmap bmp21(bmp1.getWidth(),bmp1.getHeight());
   Bitmap bmp31(bmp1.getWidth(),bmp1.getHeight());
   Bitmap bmp41(bmp1.getWidth(),bmp1.getHeight());

   screen.draw(bmp1, 0, 0);
   screen.flip();

   Pallete paleta = NarzuconaPaleta();
   dittering(bmp1, paleta);

   //to3bitBMP(bmp1,bmp11,paleta);
   screen.draw(bmp1, bmp11.getWidth(), 0);
   screen.flip();

   paleta = getPallete(bmp3);
   //dittering(bmp3, paleta);
   to3bitBMP(bmp2,bmp21,paleta);
   screen.draw(bmp21, 0, bmp21.getHeight());
    screen.flip();
   paleta = SkalaSzarosci();

   //dittering(bmp4, paleta);
   to3bitBMP(bmp3,bmp31, paleta);
   screen.draw(bmp31, bmp31.getWidth(), bmp31.getHeight());
    screen.flip();
}
