#ifdef __linux__
    #include "include/algorytmy.h"
#else
    #include "algorytmy.h"
#endif

std::string dec_to_bin(Uint8 bits)
{
    std::string bin_data;
    for(int j=0; j<8; ++j)
        bin_data = (char)(((bits>>j)&1)+48) + bin_data;
    return bin_data;
}

int notRedundantBits(Uint8 x)
{
    int ret = 8;
    for(int i=0; i<8; ++i)
    {
        if(x & 0x80) return ret;
        x<<=1;
        ret--;
    }

    return ret;
}

Uint8 * CompressedData::getDataPointer()
{
    if(data.size() == 0)
        return nullptr;
    return &(data.at(0));
}

std::vector<Uint8>& CompressedData::getDataRef()
{
    return data;
}

int CompressedData::getDataSize()
{
    return data.size();
}

unsigned long CompressedData::getBitSize()
{
    return bitSize;
}

void CompressedData::setBitSize(unsigned long bitSize)
{
    this->bitSize = bitSize;
}

void CompressedData::writeBit(Uint8 bit)
{
    int byte_index = bitSize/8;
    Uint8 bit_index = bitSize%8;
    bit &= 1;
    bit <<=bit_index;
    Uint8 mask = ~(1<<bit_index);

    //printf("DEBUG: %i %i %s %s\n", byte_index, bit_index, dec_to_bin(bit).c_str(), dec_to_bin(mask).c_str());

    while(byte_index >= data.size())
        data.push_back(0);

    data.at(byte_index) &= mask; // clear bit;
    data.at(byte_index) |= bit; // set bit if desired;
    bitSize++; //increment bit pointer;
}

Uint8 CompressedData::readBit()
{
    unsigned long address = bitSize;
    int byte_index = address/8;
    if(byte_index >= data.size()) return 0;
    Uint8 bit_index = address%8;
    Uint8 mask = (1<<bit_index);

    //printf("  DEBUG: %i %i %s\n", byte_index, bit_index, dec_to_bin(mask).c_str());
    bitSize++;
    return ((data.at(byte_index)&mask)>>bit_index);
}

void CompressedData::printData()
{
    printf("DATA:\n");

    for(int i=0; i<data.size(); ++i)
    {
        printf("%i: %i %s\n", i, data.at(i), dec_to_bin(data.at(i)).c_str());
    }
}

void CompressedData::encodeByte(Uint8 byte, int k)
{
    int divider = (1<<k);
    int quotient = byte/divider;
    int rest = byte%divider;

    std::string encoded;

    for(int i=0; i<quotient; ++i)
    {encoded += '1'; writeBit(1);}
    encoded +='0';
    writeBit(0);


    for(int i=k-1; i>=0; --i)
    {
        char bit = (((byte>>i)&1)+48);
        encoded +=bit;
        writeBit(bit);
    }

    //if(encoded.size()>8) printf("DUPPPA: \n");
    //printf(" %i BEBUG: %s %s\n",byte, dec_to_bin(byte).c_str(), encoded.c_str());
}

Uint8 CompressedData::decodeByte(int k)
{
    int quotient = 0;
    int rest =0;
    while(readBit()) quotient++;
    for(int i=0; i<k; ++i)
    {
        rest |= readBit();
        rest<<=1;
    }
    rest>>=1;

    //printf("q: %i, r: %i;\n", quotient, rest);

    int decoded = quotient*(1<<k) +rest;
    return decoded;
}

void CompressedData::dataResize(int size)
{
    data.resize(size);
}

void compression( CompressedData& out, Bit3BMP& obraz)
{
    int byteSize = obraz.data.size();
    out.dataResize(4);

    out.getDataRef().at(0) = byteSize;
    out.getDataRef().at(1) = byteSize>>8;
    out.getDataRef().at(2) = byteSize>>16;
    out.getDataRef().at(3) = byteSize>>24;


    out.setBitSize(32);

    for(Uint8 byte: obraz.data)
    {
        out.encodeByte(byte,1);
    }
}

void dekompression (Bit3BMP & out, CompressedData & in)
{
    out.data.clear();

    int byteSize = in.getDataRef().at(3);
    byteSize = (byteSize<<8) | in.getDataRef().at(2);
    byteSize = (byteSize<<8) | in.getDataRef().at(1);
    byteSize = (byteSize<<8) | in.getDataRef().at(0);

    in.setBitSize(32);

    printf("bytesize:  %i\n", byteSize);

    for(int i=0; i<byteSize; ++i)
        out.data.push_back(in.decodeByte(1));
}

void test1(Screen & screen)
{

    Bitmap bmp("obrazek1.bmp");
    screen.draw(bmp,100,100);
    Bit3BMP in,out;
    for(int i=0; i<200; ++i)
        in.data.push_back(i%8);

    CompressedData intermidiate;

    compression(intermidiate,in);

    dekompression(out,intermidiate);

    for(Uint8 byte: out.data)
    {
        printf("%i", byte);
    }

    printf("\ntest1 size: %i \n", intermidiate.getDataSize());
}


// ROZWAZANIA

/*
 * Przyjmuje liczba 0d zera do 2^32 bez znaku
 * Przesówa ją w lewo (mnoży 2) za każdym razem dekrementując n (max n = 32)
 * Dopuki albo n jest wieksze od 0 (min n =0) albo 32 bit x jest zapalony;
 *
 * Konkluzje:
 * funkcja liczby ile bitów w 32 bitowej zmiennej jest użyte do reprezentacji liczby;
 */
// static int numBits(uint32_t x)

/*
 * Inicjalizacja struktury BitStream
 * Wpisuje bufor danych
 * Pozycja bitu(?) na zero
 * wpisuje wielkość bufora(?)
 */
//static void initBitStream(BitStream* stream, uint8_t* buffer, uint32_t bytes)

/*
 * index - pozycja bitu w strukturze cofnieta o 3 miejsca (podzielona na 8)
 *  Konkluzja: index bajtu w bufoze w którym znajduje sie bit
 *
 * jezeli index jest mniejszy od rozmiaru bufora ( jest w buforze)
 *      bit - 0b111 - pozycja_bitu & 0b111
 *          Konkluzja: Pozycja bitu w bajcie w odwrocie czyli od lewej (od 0 do 7)
 *      mask - 0b11111111 xor (1<<bit)
 *          Konkluzja: Maska 8 jedynek i bit o adresie $bit na zero
 *      set = (x & 1) <<bit
 *          Konkluzja: ostatni bit w x przesunięty o adres bitu w bajcie
 *      bufor w BitStream o danym indexie - ( tenże bajt & mask) |set;
 *          Konkluzja: Czyscimy bit w bufoze i ustawiamy go wedle uznania
 *
 *      inkrementuj pozycje bitu w w strukturze
 *
 * Konkluzja:
 *      Funkcja dodoaje nowy bit w BitStream na stos bitwy w indexach od 0 w góre od lewej do prawej
 */
//static void writeBit(BitStream* stream, int x)


#define RICE_HISTORY 16
#define RICE_THRESHOLD 8
/*
 * x - słowo x ?
 * k - wartosc
 * stream - struktura
 *
 * q - słowo x przesuniete o k w prawo (podzielone przez 2^k)
 *  Konkluzja: quotient rice'a Podzielnik wynosi 2^k
 *
 * jezeli quotient jest wiekszy od THRESHOLD (8)
 *      zapisz w strukturze 8 jedynek
 *      odejmij 8 od qoutienta
 *
 *      o - liczba bitów zajetych w quotient
 *      zapisz w stukturze o jedynek
 *      zapisz w strukturze 0
 *
 *      Zapisz w strukturze binarną reprezentacje bitów od o-2 do 0 od lewej do prawej w quotient
 *
 * jeżeli quotient mniejszy od 8
 *      Zapisz w strukturze quotient jedynek
 *      Zapisz 0 w strukturze
 *          Konkluzja: zapizywanie quotientu w kodzie unarnym jeżeli quotient mnieszy od 8
 *
 * zapisz binarną reprezentacje słowa x bitów od k-1 do 0 od lewej do prawej
 *     Konkluzja: zapisywanie remaindera słowa
 *
 *
 * Konkluzja: Funkcja zapisuje jedent bajt w postaci reisa do struktury
 */

//static void encodeWord(uint32_t x, int k, BitStream* stream)


/*
 * Tworzy stream
 * incount - ilosc swłow przez ilosć bajtów w slowie
 *         Konkluzja: ilość bajtów w inpucie
 * Inicjalizacja struktury outputem o wielkosci inputu plus1;
 *
 * Historia rice'a liczba nie redundantnych bitów w pierwszych słowach
 * k - suma nieredundantnych bitów w historii
 * i - długość historii
 * k - (k+(dłogość historii/2))/długość histori
 * jesli k=0 k=1
 * pierwszy bajt w strukturze - k
 *      Konkluzja: k to pierwszy podzienik
 *
 * Dla każdego inputu od i=0 do i=incount
 *      Jezeli i>długości historii
 *          k - suma nieredundantnych bitów w hstorii
 *          k -srednia ilość redundantnych bitów +1/2
 *
 *      enkodój input za pomocą k
 *      zapisz redundantne bity w historii o indeksie i%długość historii
 *
 *
 * Jeżeli i < incount zmień pierwszy bajt w strukturze na 0 (k=0) i zakoduj ciąg bez konversji
 *
 */
//static int Compress(uint8_t* input, uint8_t* output, uint32_t inputSize)
