#include "manipulatorzdjec.h"

QPixmap zdjecie::topixmap() {
    // implementacja funkcji
    return QPixmap();
}

zdjecie* zdjecie::obroc_horyzontalnie() {
    // implementacja funkcji
    return this;
}

zdjecie* zdjecie::obroc_wertykalnie() {
    // implementacja funkcji
    return this;
}

int** alokuj_tablice_int(size_t numRows, size_t numCols)
{
   int** tablica = new int* [numRows];
   for (int i = 0; i < numRows; i++) tablica[i] = new int[numCols] ;
   return tablica;
}
std::byte** alokuj_tablice(size_t numRows, size_t numCols) {
    std::byte** tablica = new std::byte* [numRows];
    for (int i = 0; i < numRows; i++) tablica[i] = new std::byte[numCols] ;
    return tablica;
}

void zwolnij_tablice( int** tab, int wiersze){
for (int i = 0; i < wiersze; i++) delete[] tab[i];
        delete[] tab;
}
void zwolnij_tablice( std::byte** tab, int wiersze){
for (int i = 0; i < wiersze; i++) delete[] tab[i];
        delete[] tab;
}

QPixmap zdjecieRGB::topixmap()  {
    QImage image(szer, wys, QImage::Format_RGB32);

    for (int x = 0; x < szer; ++x) {
        for (int y = 0; y < wys; ++y) {
            QRgb color = qRgb(static_cast<int>(R[x][y]), static_cast<int>(G[x][y]), static_cast<int>(B[x][y]));
            image.setPixel(x, y, color);
        }
    }

    return QPixmap::fromImage(image);
}
zdjecie* zdjecieRGB::obroc_horyzontalnie() {
    zdjecieRGB* obrocone = new zdjecieRGB(*this);
    for(int start = 0; start < szer/2; start++) {
        obrocone->zamien_wiersze(start, szer - start, obrocone);
    }
    return obrocone;
}

// Implementacja funkcji obroc_wertykalnie() dla klasy zdjecieRGB
zdjecie* zdjecieRGB::obroc_wertykalnie() {
    zdjecieRGB* obrocone = new zdjecieRGB(*this);
    for(int start = 0; start < wys/2; start++) {
        obrocone->zamien_wiersze(start, wys - start, obrocone);
    }
    return obrocone;
}

 zdjecieRGB::zdjecieRGB(QPixmap pxm)
{
     //QImage nie lubi jpg, lubi PNG mozna cos tu zmienic

    QImage img = pxm.toImage();
    szer = img.width();
    wys = img.height();
    R = alokuj_tablice(szer,wys);
    G = alokuj_tablice(szer,wys);
    B = alokuj_tablice(szer,wys);

    for(int x = 0; x!= szer; x++)
        for (int y=0;y!= wys; y++ ) {
             QColor kolor = img.pixel(x,y) ;
             R[x][y] = (std::byte) kolor.red();
             G[x][y] = (std::byte) kolor.green();
             B[x][y] = (std::byte) kolor.blue();
        }

}
