#pragma once
#ifndef MANIPULATORZDJEC_H
#define MANIPULATORZDJEC_H
#include <iostream>
#include <qimage.h>
#include <QPixmap>
#include <qmessagebox.h>
#include <QColor>

std::byte** alokujTablice(size_t numRows, size_t numCols);
int** alokujTabliceInt(size_t numRows, size_t numCols);
void zwolnijTablice( std::byte** tab, int wiersze);
void zwolnijTablice( int** tab, int wiersze);

class Obraz
{
protected:
    std::string sciezka;
    int m_szerokosc;
    int m_wysokosc;

public:
    virtual QPixmap toPixmap() = 0;
    virtual void odbijWzglOsiX() = 0;
    virtual void odbijWzglOsiY() = 0;
    virtual void negatywowanie() = 0;

    int getSzerokosc() {return m_szerokosc;}
    int getWysokosc() {return m_wysokosc;}
    std::string getSciezka(){return sciezka;}
    void setSciezka(std::string s){sciezka = s;}
};

class ObrazRGB : public Obraz
{
private:
    std::byte** m_R;
    std::byte** m_G;
    std::byte** m_B;
    std::byte** m_A;

    void zamienKolumny(int kolumna1, int kolumna2);
    void zamienWiersze(int wiersz1, int wiersz2);

public:
    void odbijWzglOsiX() override;
    void odbijWzglOsiY() override;
    void negatywowanie() override;
    QPixmap toPixmap() override;

    std::byte** getKanalR() {return m_R;}
    std::byte** getKanalG() {return m_G;}
    std::byte** getKanalB() {return m_B;}

    //K. Argumentowy
    ObrazRGB(QPixmap pxm);
    //K. Przenoszący
    ObrazRGB(ObrazRGB&& other) noexcept;
    //K. Kopiujacy
    ObrazRGB(const ObrazRGB& kopia);

    ~ObrazRGB();
};

#endif
