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

    int getTransfR() {return m_transfR;}
    int getTransfG() {return m_transfG;}
    int getTransfB() {return m_transfB;}
    void setTransformacje(int transfR, int transfG, int transfB);

    void zapiszZmianeObrazu() override;
    void zapiszTransfKanaluR();
    void zapiszTransfKanaluG();
    void zapiszTransfKanaluB();
    void zerujTransformacje();
};

#endif // TRANSFORMACJE_H
