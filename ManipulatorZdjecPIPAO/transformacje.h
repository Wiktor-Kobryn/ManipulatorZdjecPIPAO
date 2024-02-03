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
private:
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

    void zapiszZmianeObrazu() override;
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
    //void wpiszWartKanalu(std::byte* wartosc, int przesuniecie);
};

#endif // TRANSFORMACJE_H
