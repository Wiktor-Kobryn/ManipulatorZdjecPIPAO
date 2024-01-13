#ifndef TRANSFORMACJE_H
#define TRANSFORMACJE_H

#include "obraz.h"
class Obraz;
class ObrazRGB;

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
    TransfPixRGB() :TransfPix() {};
    TransfPixRGB(ObrazRGB* obraz, int transfR, int transfG, int transfB);
    TransfPixRGB(ObrazRGB* obraz);

    int getTransfR() {return m_transfR;}
    int getTransfG() {return m_transfG;}
    int getTransfB() {return m_transfB;}
    void setTransformacje(int transfR, int transfG, int transfB);
    void setTransfR(int R) {m_transfR = R;}
    void setTransfG(int G) {m_transfR = G;}
    void setTransfB(int B) {m_transfR = B;}

    void zapiszZmianeObrazu() override;
    void zapiszTransfKanaluR();
    void zapiszTransfKanaluG();
    void zapiszTransfKanaluB();
    void zerujTransformacje();
    void wpiszWartKanalu(std::byte* wartosc, int przesuniecie);
};

#endif // TRANSFORMACJE_H
