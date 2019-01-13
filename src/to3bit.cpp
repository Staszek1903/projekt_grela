#ifdef __linux__
#include "include/algorytmy.h"
#else
#include "algorytmy.h"
#endif

#include <math.h>

using namespace std;

Pallete Reorder(Pallete paleta, Bitmap &in)
{
	int tab[8] = {};
	int resX = in.getWidth();
	int resY = in.getHeight();

	for (int i = 0; i < resX; ++i)
		for (int j = 0; j < resY; ++j)
		{
			tab[FindIndex(in.getPixel(i, j), paleta)]++;
		}

	Pallete ret;
	for (int j = 0; j < 8; j++)
	{
		int max = -1;
		int maxIndex;
		for (int i = 0; i < 8; i++)
		{
			if (tab[i] > max)
			{
				max = tab[i];
				maxIndex = i;
			}
		}
		tab[maxIndex] = 0;
		ret.c[j] = paleta.c[maxIndex];
	}
	return ret;
}

Pallete NarzuconaPaleta()
{
	Pallete narzuconaPaleta;
	narzuconaPaleta.c[0].r = 255;
	narzuconaPaleta.c[0].g = 255;
	narzuconaPaleta.c[0].b = 255;

	narzuconaPaleta.c[1].r = 0;
	narzuconaPaleta.c[1].g = 0;
	narzuconaPaleta.c[1].b = 0;

	narzuconaPaleta.c[2].r = 255;
	narzuconaPaleta.c[2].g = 0;
	narzuconaPaleta.c[2].b = 0;

	narzuconaPaleta.c[3].r = 0;
	narzuconaPaleta.c[3].g = 255;
	narzuconaPaleta.c[3].b = 0;

	narzuconaPaleta.c[4].r = 0;
	narzuconaPaleta.c[4].g = 0;
	narzuconaPaleta.c[4].b = 255;

	narzuconaPaleta.c[5].r = 255;
	narzuconaPaleta.c[5].g = 255;
	narzuconaPaleta.c[5].b = 0;

	narzuconaPaleta.c[6].r = 0;
	narzuconaPaleta.c[6].g = 255;
	narzuconaPaleta.c[6].b = 255;

	narzuconaPaleta.c[7].r = 255;
	narzuconaPaleta.c[7].g = 0;
	narzuconaPaleta.c[7].b = 255;
	return narzuconaPaleta;
}

Pallete SkalaSzarosci()
{
	Pallete paleta;
	paleta.c[0].r = 0;
	paleta.c[0].g = 0;
	paleta.c[0].b = 0;

	paleta.c[1].r = 36;
	paleta.c[1].g = 36;
	paleta.c[1].b = 36;

	paleta.c[2].r = 72;
	paleta.c[2].g = 72;
	paleta.c[2].b = 72;

	paleta.c[3].r = 108;
	paleta.c[3].g = 108;
	paleta.c[3].b = 108;

	paleta.c[4].r = 144;
	paleta.c[4].g = 144;
	paleta.c[4].b = 144;

	paleta.c[5].r = 180;
	paleta.c[5].g = 180;
	paleta.c[5].b = 180;

	paleta.c[6].r = 216;
	paleta.c[6].g = 216;
	paleta.c[6].b = 216;

	paleta.c[7].r = 255;
	paleta.c[7].g = 255;
	paleta.c[7].b = 255;
	return paleta;
}

Pallete SkalaSzarosci(Pallete paleta)
{
	Pallete ret;
	for (int i = 0; i < 8; i++)
	{
		int BW = paleta.c[i].r*0.299 + paleta.c[i].g*0.587 + paleta.c[i].b*0.114;
		ret.c[i].r = BW;
		ret.c[i].g = BW;
		ret.c[i].b = BW;
	}
	return ret;
}

SDL_Color FindColor(SDL_Color pixel, Pallete paleta)
{
	int minDistance = 1000;
	int minIndeks = 0;
	for (int i = 0; i < 8; ++i)
	{
		int distance = sqrt(pow(pixel.r - paleta.c[i].r, 2) + pow(pixel.g - paleta.c[i].g, 2) + pow(pixel.b - paleta.c[i].b, 2));
		if (distance < minDistance)
		{
			minDistance = distance;
			minIndeks = i;
		}
	}
	return paleta.c[minIndeks];
}

int FindIndex(SDL_Color pixel, Pallete paleta)
{
	int minDistance = 1000;
	int minIndeks = 0;
	for (int i = 0; i < 8; ++i)
	{
		int distance = sqrt(pow(pixel.r - paleta.c[i].r, 2) + pow(pixel.g - paleta.c[i].g, 2) + pow(pixel.b - paleta.c[i].b, 2));
		if (distance < minDistance)
		{
			minDistance = distance;
			minIndeks = i;
		}
	}
	return minIndeks;
}

void to3bitBMP(Bitmap &in, Bitmap &out, Pallete paleta)
{
	int resX = in.getWidth();
	int resY = in.getHeight();
    out.create(resX,resY);

	for (int i = 0; i < resX; ++i)
		for (int j = 0; j < resY; ++j)
		{
			out.setPixel(i, j, FindColor(in.getPixel(i, j), paleta));
		}
}

Bit3BMP to3bitTab(Bitmap &in, Pallete paleta)
{
	Bit3BMP ret;
    ret.width = in.getWidth();
    ret.height = in.getHeight();
    ret.paleta = paleta;

    ret.data.resize(ret.width * ret.height);

	int indeks = 0;
    for (int i = 0; i < ret.height; ++i)
        for (int j = 0; j < ret.width; ++j)
		{
			ret.data[indeks++] = FindIndex(in.getPixel(j, i), paleta);
		}
	return ret;
}

void bit3toBitmap(Bit3BMP & in, Bitmap &out)
{
    out.create(in.width,in.height);
    auto iter = in.data.begin();
    for (int i = 0; i < in.height; ++i)
        for (int j = 0; j < in.width; ++j)
        {
            out.setPixel(j,i,in.paleta.c[*iter]);
            iter++;
        }
}

void test4(Screen & screen)
{
	Bitmap bmp("obrazek2.bmp");
	Bitmap bmp1("obrazek2.bmp");
	Bitmap bmp2("obrazek2.bmp");
	Bitmap bmp3("obrazek2.bmp");
	Bitmap bmp4("obrazek2.bmp");

	screen.draw(bmp, 0, 0);
	Pallete paleta;

	paleta = getPallete(bmp);
	paleta = Reorder(paleta, bmp);
	to3bitBMP(bmp, bmp1, paleta);
	screen.draw(bmp1, bmp1.getWidth(), 0);

	paleta = SkalaSzarosci(paleta);
	paleta = Reorder(paleta, bmp);
	to3bitBMP(bmp, bmp4, paleta);
	screen.draw(bmp4, 0, 0);

	paleta = NarzuconaPaleta();
	paleta = Reorder(paleta, bmp);
	to3bitBMP(bmp, bmp2, paleta);
	screen.draw(bmp2, 0, bmp2.getHeight());

	paleta = SkalaSzarosci();
	paleta = Reorder(paleta, bmp);
	to3bitBMP(bmp, bmp3, paleta);
	screen.draw(bmp3, bmp3.getWidth(), bmp3.getHeight());
}
