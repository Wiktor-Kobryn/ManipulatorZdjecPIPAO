#include "manipulatorzdjec.h"


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
