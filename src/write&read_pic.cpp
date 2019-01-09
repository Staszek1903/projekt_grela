#ifdef __linux__
    #include "include/algorytmy.h"
#else
    #include "algorytmy.h"
#endif

#include <iostream>

using namespace std;

void seeExceptions(EXCEPTION_CODE error)
{
	switch (error) {
	case EXCEPTION_CODE::openError:
		cerr << "Blad otwarcia pliku odczytu" << endl;
		break;
	case EXCEPTION_CODE::createError:
		cerr << "Blad tworzenia pliku zapisu" << endl;
		break;
	case EXCEPTION_CODE::alloc_problem:
		cerr << "Blad alokacji tablicy" << endl;
		break;
	default:
		cerr << "Nieznany blad";
		break;
	}
}


void OpenFile(fstream &file)
{
	string nazwa_pliku;
	cout << "Podaj nazwe pliku wejsciowego (Bez .okon)" << endl;
	cin >> nazwa_pliku;
	nazwa_pliku = nazwa_pliku + ".okon";
	file.open(nazwa_pliku.c_str(), ios::in);

	try
	{
		if (!file.is_open())
		{
			throw EXCEPTION_CODE::openError;
		}
	}

	catch (EXCEPTION_CODE error)
	{
		seeExceptions(error);

	}

}


void CreateFile(fstream &file)
{
	string nazwa_pliku = "obrazek";
	nazwa_pliku = nazwa_pliku + ".okon";
	file.open(nazwa_pliku.c_str(), ios::out | ios::binary);
	try
	{
		if (!file.is_open())
		{
			throw EXCEPTION_CODE::createError;
	    }
	}

	catch (EXCEPTION_CODE error)
	{
		seeExceptions(error);

	}
}

void write_to_okon(fstream& file, CompressedData& data, Pallete& paleta,int typeOfPallete, Bitmap& in)
{
    CreateFile(file);

    string format = "OKON";
    file<<format<<endl;

    int width = in.getWidth();
    int height = in.getHeight();
    file<<width<<" "<<height<<endl;

    int size = data.getDataSize();
    Uint8 * raw_data = data.getDataPointer();




    /*

    if(typeOfPallete == 0)
    else if(typeOfPallete == 1)
    else if(typeOfPallete == 2)
    */
    {
        for(int i=0; i < 8; i++ )
        {
            file<<paleta.c[i].r<<" "<<paleta.c[i].g<<" "<<paleta.c[i].b<<endl;
        }
    }


    Uint8* dataPointer = data.getDataPointer();

    vector <Uint8> pixels = data.getDataRef();
    int vec_size = data.getDataSize();

    for(int i = 0 ; i < vec_size; i++ )
    {
        file<<pixels[i]<<endl;
    }



}


void test5(Screen & screen)
{
    fstream plik;
    CompressedData data;
    Bitmap in("obrazek1.bmp");
    Pallete paleta = SkalaSzarosci();
    write_to_okon(plik , data , paleta, 0, in);







}


