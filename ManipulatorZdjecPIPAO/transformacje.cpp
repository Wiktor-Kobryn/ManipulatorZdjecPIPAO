#include "transformacje.h"

//TransfPixRGB

TransfPixRGB::TransfPixRGB(ObrazRGB* obraz, int transfR, int transfG, int transfB)
    :TransfPix(obraz)
{
    setTransformacje(transfR, transfG, transfB);
}

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

void TransfPixRGB::zapiszTransfKanaluR()
{
    std::byte** kanalR = m_obraz->getKanalR();

    for(int i = 0; i < m_obraz->getSzerokosc(); i++)
    {
        for(int j = 0; j < m_obraz->getWysokosc(); j++)
        {
            kanalR[i][j] = static_cast<std::byte>(static_cast<int>(kanalR[i][j]) + m_transfR);

            //nie jest potrzebne ze względu na to że mamy byte ale
            //jak to ucinanie wartości przy cast dokładnie działa to nie wiem xd
            /*
            if(kanalR[i][j] > static_cast<std::byte>(255))
                kanalR[i][j] = static_cast<std::byte>(static_cast<int>(kanalR[i][j]) - 255);
            */
        }
    }
}

void TransfPixRGB::zapiszTransfKanaluG()
{
    std::byte** kanalG = m_obraz->getKanalG();

    for(int i = 0; i < m_obraz->getSzerokosc(); i++)
    {
        for(int j = 0; j < m_obraz->getWysokosc(); j++)
        {
            kanalG[i][j] = static_cast<std::byte>(static_cast<int>(kanalG[i][j]) + m_transfG);
        }
    }
}

void TransfPixRGB::zapiszTransfKanaluB()
{
    std::byte** kanalB = m_obraz->getKanalB();

    for(int i = 0; i < m_obraz->getSzerokosc(); i++)
    {
        for(int j = 0; j < m_obraz->getWysokosc(); j++)
        {
            kanalB[i][j] = static_cast<std::byte>(static_cast<int>(kanalB[i][j]) + m_transfB);
        }
    }
}

void TransfPixRGB::zerujTransformacje()
{
    m_transfR = 0;
    m_transfG = 0;
    m_transfB = 0;
}
