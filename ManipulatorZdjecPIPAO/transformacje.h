#ifndef TRANSFORMACJE_H
#define TRANSFORMACJE_H

#include "obraz.h"
#include <algorithm>
class Obraz;
class ObrazRGB;
class PixelHSL;
class PixelRGB;
class PixelCMYK;

class PixelRGB
{
private:
    int m_R = 0, m_G = 0, m_B = 0;

public:
    PixelRGB(int R, int G, int B);
    PixelRGB() {}

    int getR() {return m_R;}
    int getG() {return m_G;}
    int getB() {return m_B;}
    void setR(int R);
    void setG(int G);
    void setB(int B);

    PixelHSL konwertujDoHSL();
    PixelCMYK konwertujDoCMYK();
};

class PixelHSL
{
private:
    int m_H = 0, m_S = 0, m_L = 0;

public:
    PixelHSL(int H, int S, int L);
    PixelHSL() {}

    int getH() {return m_H;}
    int getS() {return m_S;}
    int getL() {return m_L;}
    void setH(int H);
    void setS(int S);
    void setL(int L);

    PixelRGB konwertujDoRGB();
};

class PixelCMYK
{
private:
    int m_C = 0, m_M = 0, m_Y = 0, m_K = 0;

public:
    PixelCMYK(int C, int M, int Y, int K);
    PixelCMYK() {}

    int getC() {return m_C;}
    int getM() {return m_M;}
    int getY() {return m_Y;}
    int getK() {return m_K;}
    void setC(int C);
    void setM(int M);
    void setY(int Y);
    void setK(int K);

    PixelRGB konwertujDoRGB();
};

//<<abstract>>
class TransfPix
{
protected:
    ObrazRGB* m_obraz = nullptr;

public:
    TransfPix(ObrazRGB* obraz) {m_obraz = obraz;}
    TransfPix() {}

    void setObraz(ObrazRGB* obraz) {m_obraz = obraz;}
    ObrazRGB* getObraz() {return m_obraz;}

    virtual void zapiszZmianeObrazu() = 0;
};

class TransfPixRGB : public TransfPix
{
protected:
    int m_transfR = 0, m_transfG = 0, m_transfB = 0;

public:
    TransfPixRGB() :TransfPix() {}
    TransfPixRGB(ObrazRGB* obraz, int transfR, int transfG, int transfB);
    TransfPixRGB(ObrazRGB* obraz);

    int getTransfR() {return m_transfR;}
    int getTransfG() {return m_transfG;}
    int getTransfB() {return m_transfB;}
    void setTransformacje(int transfR, int transfG, int transfB);
    void setTransfR(int R) {m_transfR = R;}
    void setTransfG(int G) {m_transfG = G;}
    void setTransfB(int B) {m_transfB = B;}

    virtual void zapiszZmianeObrazu() override;
    void zapiszTransfKanaluR();
    void zapiszTransfKanaluG();
    void zapiszTransfKanaluB();
    void zerujTransformacje();
    void wpiszWartKanalu(std::byte* wartosc, int przesuniecie);
};

class TransfPixHSL : public TransfPix
{
private:
    int m_transfH = 0, m_transfS = 0, m_transfL = 0;

public:
    TransfPixHSL() :TransfPix() {}
    TransfPixHSL(ObrazRGB* obraz, int transfH, int transfS, int transfL);
    TransfPixHSL(ObrazRGB* obraz);

    int getTransfH() {return m_transfH;}
    int getTransfS() {return m_transfS;}
    int getTransfL() {return m_transfL;}
    void setTransformacje(int transfH, int transfS, int transfL);
    void setTransfH(int H) {m_transfH = H;}
    void setTransfS(int S) {m_transfS = S;}
    void setTransfL(int L) {m_transfL = L;}

    void zapiszZmianeObrazu() override;
    void zerujTransformacje();
};

class TransfPixCMYK : public TransfPix
{
private:
    int m_transfC = 0, m_transfM = 0, m_transfY = 0, m_transfK = 0;

public:
    TransfPixCMYK() :TransfPix() {}
    TransfPixCMYK(ObrazRGB* obraz, int transfC, int transfM, int transfY, int transfK);
    TransfPixCMYK(ObrazRGB* obraz);

    int getTransfC() {return m_transfC;}
    int getTransfM() {return m_transfM;}
    int getTransfY() {return m_transfY;}
    int getTransfK() {return m_transfK;}
    void setTransformacje(int transfC, int transfM, int transfY, int transfK);
    void setTransfC(int C) {m_transfC = C;}
    void setTransfM(int M) {m_transfM = M;}
    void setTransfY(int Y) {m_transfY = Y;}
    void setTransfK(int K) {m_transfK = K;}

    void zapiszZmianeObrazu() override;
    void zerujTransformacje();
};

class TransfPixKlucz : public TransfPixRGB
{
private:
    bool m_kolorNieWybrany = true;
    PixelRGB m_kolorKluczowania;
    int m_progKluczowania = 0, m_progKluczowaniaMemory = 0;

public:
    TransfPixKlucz() {}
    TransfPixKlucz(ObrazRGB* obraz, int transfR, int transfG, int transfB);
    TransfPixKlucz(ObrazRGB* obraz)
        :TransfPixRGB(obraz) {}

    void setProgKluczowania(int prog);
    int getProgKluczowania() {return m_progKluczowania;}
    void zapiszZmianeObrazu() override;
};

#endif // TRANSFORMACJE_H
