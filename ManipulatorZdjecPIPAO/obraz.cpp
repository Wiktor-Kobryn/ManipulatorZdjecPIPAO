#include "obraz.h"

////////////////////////////////////////////////////////////////////
//Obraz
////////////////////////////////////////////////////////////////////

//K: W sumie to mogliśmy zrobić to Pure Virtual =0;

QPixmap Obraz::toPixmap() {
    // implementacja funkcji
    return QPixmap();
}

void Obraz::odbijWzglOsiX() {
    // implementacja funkcji
    //return this;
}

void Obraz::odbijWzglOsiY() {
    // implementacja funkcji
    std::cerr<<"jestem zdjecie_wert";
    //return this;
}


////////////////////////////////////////////////////////////////////
//ObrazRGB
////////////////////////////////////////////////////////////////////

int** alokujTabliceInt(size_t numRows, size_t numCols)
{
   int** tablica = new int* [numRows];
   for (int i = 0; i < numRows; i++) tablica[i] = new int[numCols] ;
   return tablica;
}
std::byte** alokujTablice(size_t numRows, size_t numCols)
{
    std::byte** tablica = new std::byte* [numRows];
    for (int i = 0; i < numRows; i++) tablica[i] = new std::byte[numCols] ;
    return tablica;
}
void zwolnijTablice( int** tab, int wiersze)
{
for (int i = 0; i < wiersze; i++) delete[] tab[i];
        delete[] tab;
}
void zwolnijTablice( std::byte** tab, int wiersze)
{
for (int i = 0; i < wiersze; i++) delete[] tab[i];
        delete[] tab;
}

QPixmap ObrazRGB::toPixmap()
{
    QImage image(m_szerokosc, m_wysokosc, QImage::Format_RGBA64);

    for (int x = 0; x < m_szerokosc; ++x) {
        for (int y = 0; y < m_wysokosc; ++y) {
            QColor col = qRgba(static_cast<int>(m_R[x][y]),
                             static_cast<int>(m_G[x][y]),
                             static_cast<int>(m_B[x][y]),
                             static_cast<int>(m_A[x][y]));

            image.setPixelColor(x, y, col);
        }
    }

    return QPixmap::fromImage(image);
}


void ObrazRGB::odbijWzglOsiX()
{
    for(int start = 0; start < m_szerokosc/2; start++)
    {
        zamienKolumny(start, m_szerokosc - start);
    }
}

void ObrazRGB::odbijWzglOsiY()
{
    for(int start = 0; start < m_wysokosc/2; start++)
    {
        zamienWiersze(start, m_wysokosc - start);
    }
}

void ObrazRGB::negatywowanie() {
    for(int x = 0; x!= m_szerokosc; x++)
        for (int y=0;y!= m_wysokosc; y++ ) {
             m_R[x][y] = (std::byte) (255 - (int)m_R[x][y]);
             m_G[x][y] = (std::byte) (255 - (int)m_G[x][y]);
             m_B[x][y] = (std::byte) (255 - (int)m_B[x][y]);
        }
 }
 ObrazRGB::ObrazRGB(QPixmap pxm)
{
    //QImage nie lubi jpg, lubi PNG mozna cos tu zmienic

    QImage img = pxm.toImage();
    m_szerokosc = img.width();
    m_wysokosc = img.height();
    m_R = alokujTablice(m_szerokosc,m_wysokosc);
    m_G = alokujTablice(m_szerokosc,m_wysokosc);
    m_B = alokujTablice(m_szerokosc,m_wysokosc);
    m_A = alokujTablice(m_szerokosc,m_wysokosc);

    for(int x = 0; x!= m_szerokosc; x++)
        for (int y=0;y!= m_wysokosc; y++ ) {
             QColor kolor = img.pixel(x,y) ;
             m_R[x][y] = (std::byte) kolor.red();
             m_G[x][y] = (std::byte) kolor.green();
             m_B[x][y] = (std::byte) kolor.blue();
             m_A[x][y] = (std::byte) kolor.alpha();
        }

}

ObrazRGB::ObrazRGB(ObrazRGB&& other) noexcept
    : m_R(nullptr), m_G(nullptr), m_B(nullptr)
{
    // Przenoszenie zasobów z 'other' do bieżącego obiektu
    m_R = other.m_R;
    m_G = other.m_G;
    m_B = other.m_B;
    m_szerokosc = other.m_szerokosc;
    m_wysokosc = other.m_wysokosc;

    // Resetowanie zasobów w 'other'
    other.m_R = nullptr;
    other.m_G = nullptr;
    other.m_B = nullptr;
    other.m_szerokosc = 0;
    other.m_wysokosc = 0;
}

ObrazRGB::ObrazRGB(const ObrazRGB& kopia)
{
    m_szerokosc = kopia.m_szerokosc;
    m_wysokosc = kopia.m_wysokosc;

    m_R = alokujTablice(m_szerokosc, m_wysokosc);
    m_G = alokujTablice(m_szerokosc, m_wysokosc);
    m_B = alokujTablice(m_szerokosc, m_wysokosc);

    for (int x = 0; x < m_szerokosc; x++)
    {
        for (int y = 0; y < m_wysokosc; y++)
        {
            m_R[x][y] = kopia.m_R[x][y];
            m_G[x][y] = kopia.m_G[x][y];
            m_B[x][y] = kopia.m_B[x][y];
        }
    }
}

ObrazRGB::~ObrazRGB()
{
    qDebug() << "[ObrazRGB]Przestaje Istniec";
    if(m_R!=nullptr)  zwolnijTablice(m_R, m_wysokosc);
    if(m_B!=nullptr)  zwolnijTablice(m_B, m_wysokosc);
    if(m_G!=nullptr)  zwolnijTablice(m_G, m_wysokosc);
    if(m_A!=nullptr)  zwolnijTablice(m_A, m_wysokosc);

}

void ObrazRGB::zamienWiersze(int wiersz1, int wiersz2)
{
    if (wiersz1 < 0 || wiersz2 < 0 || wiersz1 >= m_wysokosc || wiersz2 >= m_wysokosc)
    {
        std::cerr << "Nieprawidlowe numery wierszy" << std::endl;
        return;
    }

    for (int x = 0; x < m_szerokosc; x++)
    {
        std::swap(m_R[x][wiersz1], m_R[x][wiersz2]);
        std::swap(m_G[x][wiersz1], m_G[x][wiersz2]);
        std::swap(m_B[x][wiersz1], m_B[x][wiersz2]);
    }
}

void ObrazRGB::zamienKolumny(int kolumna1, int kolumna2)
{
    if (kolumna1 < 0 || kolumna2 < 0 || kolumna1 >= m_szerokosc || kolumna2 >= m_szerokosc) {
        std::cerr << "Nieprawidlowe numery kolumn" << std::endl;
        return;
    }

    for (int y = 0; y < m_wysokosc; y++) {
        std::swap(m_R[kolumna1][y], m_R[kolumna2][y]);
        std::swap(m_G[kolumna1][y], m_G[kolumna2][y]);
        std::swap(m_B[kolumna1][y], m_B[kolumna2][y]);
    }
}
