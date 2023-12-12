#ifndef MANIPULATORZDJEC_H
#define MANIPULATORZDJEC_H
#include <iostream>
#include <qimage.h>
#include <QPixmap>
std::byte** alokuj_tablice(size_t numRows, size_t numCols) {
    std::byte** tablica = new std::byte* [numRows];
    for (int i = 0; i < numRows; i++) tablica[i] = new std::byte[numCols] ;
    return tablica;
}
int** alokuj_tablice_int(size_t numRows, size_t numCols) {
    int** tablica = new int* [numRows];
    for (int i = 0; i < numRows; i++) tablica[i] = new int[numCols] ;
    return tablica;
}

void zwolnij_tablice( std::byte** tab, int wiersze){
for (int i = 0; i < wiersze; i++) delete[] tab[i];
        delete[] tab;
}
void zwolnij_tablice( int** tab, int wiersze){
for (int i = 0; i < wiersze; i++) delete[] tab[i];
        delete[] tab;
}


class zdjecie
{
protected:
    std::string sciezka;
    int szer;
    int wys;

public:
    virtual zdjecie obroc_horyzontalnie();
    virtual zdjecie obroc_wertykalnie();
};
class zdjecieRGB : public zdjecie
{
private:
    std::byte** R;
    std::byte** G;
    std::byte** B;

    void zamien_kolumny(int kolumna1, int kolumna2, zdjecieRGB* Z) {
        if (kolumna1 < 0 || kolumna2 < 0 || kolumna1 >= szer || kolumna2 >= szer) {
            std::cerr << "Nieprawidlowe numery kolumn" << std::endl;
            return;
        }

        for (int y = 0; y < wys; y++) {
            std::swap(Z->R[kolumna1][y], Z->R[kolumna2][y]);
            std::swap(Z->G[kolumna1][y], Z->G[kolumna2][y]);
            std::swap(Z->B[kolumna1][y], Z->B[kolumna2][y]);
        }
    }
    void zamien_wiersze(int wiersz1, int wiersz2, zdjecieRGB* Z) {
        if (wiersz1 < 0 || wiersz2 < 0 || wiersz1 >= wys || wiersz2 >= wys) {
            std::cerr << "Nieprawidlowe numery wierszy" << std::endl;
            return;
        }

        for (int x = 0; x < szer; x++) {
            std::swap(Z->R[x][wiersz1], Z->R[x][wiersz2]);
            std::swap(Z->G[x][wiersz1], Z->G[x][wiersz2]);
            std::swap(Z->B[x][wiersz1], Z->B[x][wiersz2]);
        }
    }
public:

    zdjecie obroc_horyzontalnie() override{
     zdjecieRGB obrocone = *(this);
     for(int start=0;start<szer/2 ;start++){
         zamien_wiersze(start,szer-start, &obrocone);
     }

     return obrocone;
    }
    zdjecie obroc_wertykalnie() override{
          zdjecieRGB obrocone = *(this);
          for(int start=0;start<wys/2 ;start++){
              zamien_wiersze(start,wys-start, &obrocone);
          }
          return obrocone;
    }


    //Konstrukto ry
    //Argumentowy
    zdjecieRGB(QPixmap pxm)
    {
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
    // kopiujacy
    zdjecieRGB(const zdjecieRGB& kopia){
          szer = kopia.szer;
          wys = kopia.wys;

          R = alokuj_tablice(szer, wys);
          G = alokuj_tablice(szer, wys);
          B = alokuj_tablice(szer, wys);

          for (int x = 0; x < szer; x++)
              for (int y = 0; y < wys; y++) {
                  R[x][y] = kopia.R[x][y];
                  G[x][y] = kopia.G[x][y];
                  B[x][y] = kopia.B[x][y];
              }

    }
    ~zdjecieRGB(){
        if(R!=nullptr)  zwolnij_tablice(R, wys);
        if(B!=nullptr)  zwolnij_tablice(B, wys);
        if(G!=nullptr)  zwolnij_tablice(G, wys);
    }
    friend class zdjecieRGB;
};
/*
class zdjecieHSL : public zdjecie
{
private:
    int ** H;
    std::byte** S;
    std::byte** L;
public:
    zdjecieHSL(QImage img)
    {
        szer = img.width();
        wys = img.height();
        H = alokuj_tablice_int(szer,wys);
        S = alokuj_tablice(szer,wys);
        L = alokuj_tablice(szer,wys);

        for(int x = 0; x!= szer; x++)
            for (int y=0;y!= wys; y++ ) {
                 QColor kolor = img.pixel(x,y) ;
                 H[x][y] = kolor.hue();
                 S[x][y] = (std::byte) kolor.saturation();
                 L[x][y] = (std::byte) kolor.lightness();
            }
    }

    ~zdjecieHSL(){
        if(H!=nullptr)  zwolnij_tablice(H, wys);
        if(S!=nullptr)  zwolnij_tablice(S, wys);
        if(L!=nullptr)  zwolnij_tablice(L, wys);
    }
}; */
#endif
