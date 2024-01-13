#include "transformacje.h"

//TransfPixRGB

TransfPixRGB::TransfPixRGB(ObrazRGB* obraz, int transfR, int transfG, int transfB)
    :TransfPix(obraz)
{
    setTransformacje(transfR, transfG, transfB);
}

TransfPixRGB::TransfPixRGB(ObrazRGB* obraz)
    :TransfPix(obraz)
{}


void TransfPixRGB::setTransformacje(int transfR, int transfG, int transfB)
{
    m_transfB = transfB;
    m_transfG = transfG;
    m_transfR = transfR;
}

void TransfPixRGB::zapiszZmianeObrazu()
{
    if(m_transfR != 0)
        zapiszTransfKanaluR();
    if(m_transfG != 0)
        zapiszTransfKanaluG();
    if(m_transfB != 0)
        zapiszTransfKanaluB();

    zerujTransformacje();
}

void TransfPixRGB::wpiszWartKanalu(std::byte* wartosc, int przesuniecie)
{
    int nowaWartosc = static_cast<int>(*wartosc) + przesuniecie;

    if(nowaWartosc > 255)
        nowaWartosc = 255;
    else if(nowaWartosc < 0)
        nowaWartosc = 0;

    *wartosc = static_cast<std::byte>(nowaWartosc);
}

void TransfPixRGB::zapiszTransfKanaluR()
{
    std::byte** kanalR = m_obraz->getKanalR();

    for(int i = 0; i < m_obraz->getSzerokosc(); i++)
    {
        for(int j = 0; j < m_obraz->getWysokosc(); j++)
        {
            wpiszWartKanalu(&kanalR[i][j], m_transfR);
        }
    }
    zerujTransformacje();
}

void TransfPixRGB::zapiszTransfKanaluG()
{
    std::byte** kanalG = m_obraz->getKanalG();

    for(int i = 0; i < m_obraz->getSzerokosc(); i++)
    {
        for(int j = 0; j < m_obraz->getWysokosc(); j++)
        {
            wpiszWartKanalu(&kanalG[i][j], m_transfG);
        }
    }
    zerujTransformacje();
}

void TransfPixRGB::zapiszTransfKanaluB()
{
    std::byte** kanalB = m_obraz->getKanalB();

    for(int i = 0; i < m_obraz->getSzerokosc(); i++)
    {
        for(int j = 0; j < m_obraz->getWysokosc(); j++)
        {
            wpiszWartKanalu(&kanalB[i][j], m_transfB);
        }
    }
    zerujTransformacje();
}

void TransfPixRGB::zerujTransformacje()
{
    m_transfR = 0;
    m_transfG = 0;
    m_transfB = 0;
}
