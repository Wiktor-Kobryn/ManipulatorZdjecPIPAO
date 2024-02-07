#include "transformacje.h"
using namespace std;

//////////////////////////////
//PixelRGB
//////////////////////////////

PixelRGB::PixelRGB(int R, int G, int B)
{
    setR(R);
    setG(G);
    setB(B);
}

void PixelRGB::setR(int R)
{
    if(R < 0)
        m_R = 0;
    else if(R > 255)
        m_R = 255;
    else
        m_R = R;
}

void PixelRGB::setG(int G)
{
    if(G < 0)
        m_G = 0;
    else if(G > 255)
        m_G = 255;
    else
        m_G = G;
}

void PixelRGB::setB(int B)
{
    if(B < 0)
        m_B = 0;
    else if(B > 255)
        m_B = 255;
    else
        m_B = B;
}

PixelHSL PixelRGB::konwertujDoHSL()
{
    //wzor
    //https://www.rapidtables.com/convert/color/rgb-to-hsl.html

    //wartosci pomocnicze
    double Rp = m_R / 255.0;
    double Gp = m_G / 255.0;
    double Bp = m_B / 255.0;

    double Cmax = max(Rp, max(Gp, Bp));
    double Cmin = min(Rp, min(Gp, Bp));

    double delta = Cmax - Cmin;

    //wyliczenie hue
    int H = 0;

    if (delta == 0)
        H = 0;
    else if (Cmax == Rp)
        H = 60 * fmod(((Gp - Bp) / delta), 6.0);
    else if (Cmax == Gp)
        H = 60 * (((Bp - Rp) / delta) + 2);
    else if (Cmax == Bp)
        H = 60 * (((Rp - Gp) / delta) + 4);

    //wyliczenie lightness
    double L = (Cmax + Cmin) / 2.0;

    //wyliczenie saturation
    double S = 0;

    if(delta == 0)
        S = 0;
    else
        S = delta / (1.0 - abs(2.0 * L - 1.0));

    //przeskalowanie zapisu z zakresu <0;1> do <0;100>
    L*=100;
    S*=100;

    return PixelHSL(H, (int)S, (int)L);
}

PixelCMYK PixelRGB::konwertujDoCMYK()
{
    //wzor
    //https://www.rapidtables.com/convert/color/rgb-to-cmyk.html

    //wartosci pomocnicze
    double Rp = m_R / 255.0;
    double Gp = m_G / 255.0;
    double Bp = m_B / 255.0;

    double Kp = 1.0 - max(Rp, max(Gp, Bp));
    double x = 1.0 - Kp;

    double Cp = 1.0 - Rp / x;
    double Mp = 1.0 - Gp / x;
    double Yp = 1.0 - Bp / x;

    //zmiana zakresu na <0;100>
    int C = (int)(Cp * 100.0);
    int M = (int)(Mp * 100.0);
    int Y = (int)(Yp * 100.0);
    int K = (int)(Kp * 100.0);

    return PixelCMYK(C, M, Y, K);
}

//////////////////////////////
//PixelHSL
//////////////////////////////

PixelHSL::PixelHSL(int H, int S, int L)
{
    setH(H);
    setS(S);
    setL(L);
}

void PixelHSL::setH(int H)
{
    //po przekroczeniu 360 stopni powrot do 0
    if(H < 0 || H >= 360)
        m_H = 0;
    else
        m_H = H;
}

void PixelHSL::setS(int S)
{
    if(S < 0)
        m_S = 0;
    else if(S > 100)
        m_S = 100;
    else
        m_S = S;
}

void PixelHSL::setL(int L)
{
    if(L < 0)
        m_L = 0;
    else if(L > 100)
        m_L = 100;
    else
        m_L = L;
}

PixelRGB PixelHSL::konwertujDoRGB()
{
    //wzor
    //https://www.rapidtables.com/convert/color/hsl-to-rgb.html

    //wartosci pomocnicze
    double H = m_H;
    double S = m_S / 100.0;
    double L = m_L / 100.0;

    double C = (1.0 - abs(2.0 * L - 1.0)) * S;
    double X = C * (1.0 - abs(fmod(H / 60.0, 2.0) - 1.0));
    double m = L - C / 2.0;

    //wyznaczenie wartości RGB prim
    double Rp = 0, Gp = 0, Bp = 0;

    if(0 <= H && H < 60)
    {
        Rp = C;
        Gp = X;
        Bp = 0;
    }
    else if(60 <= H && H < 120)
    {
        Rp = X;
        Gp = C;
        Bp = 0;
    }
    else if(120 <= H && H < 180)
    {
        Rp = 0;
        Gp = C;
        Bp = X;
    }
    else if(180 <= H && H < 240)
    {
        Rp = 0;
        Gp = X;
        Bp = C;
    }
    else if(240 <= H && H < 300)
    {
        Rp = X;
        Gp = 0;
        Bp = C;
    }
    else
    {
        Rp = C;
        Gp = 0;
        Bp = X;
    }

    //przeksztalcenie wartosci na RGB (integer)
    int R = (int)((Rp + m) * 255.0);
    int G = (int)((Gp + m) * 255.0);
    int B = (int)((Bp + m) * 255.0);

    return PixelRGB(R, G, B);
}

//////////////////////////////
//PixelCMYK
//////////////////////////////

PixelCMYK::PixelCMYK(int C, int M, int Y, int K)
{
    setC(C);
    setM(M);
    setY(Y);
    setK(K);
}

void PixelCMYK::setC(int C)
{
    if(C < 0)
        m_C = 0;
    else if(C > 100)
        m_C = 100;
    else
        m_C = C;
}

void PixelCMYK::setM(int M)
{
    if(M < 0)
        m_M = 0;
    else if(M > 100)
        m_M = 100;
    else
        m_M = M;
}

void PixelCMYK::setY(int Y)
{
    if(Y < 0)
        m_Y = 0;
    else if(Y > 100)
        m_Y = 100;
    else
        m_Y = Y;
}

void PixelCMYK::setK(int K)
{
    if(K < 0)
        m_K = 0;
    else if(K > 100)
        m_K = 100;
    else
        m_K = K;
}

PixelRGB PixelCMYK::konwertujDoRGB()
{
    //wzor
    //https://www.rapidtables.com/convert/color/cmyk-to-rgb.html

    //wartosci pomocnicze - zmiana zakresow na <0;1>
    double C = (double)m_C / 100.0;
    double M = (double)m_M / 100.0;
    double Y = (double)m_Y / 100.0;
    double K = (double)m_K / 100.0;

    double x = 255.0 * (1.0 - K);

    int R = (int)(x * (1.0 - C));
    int G = (int)(x * (1.0 - M));
    int B = (int)(x * (1.0 - Y));

    return PixelRGB(R, G, B);
}

//////////////////////////////
//TransfPixRGB
//////////////////////////////

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

//////////////////////////////
//TransfPixHSL
//////////////////////////////

TransfPixHSL::TransfPixHSL(ObrazRGB* obraz, int transfH, int transfS, int transfL)
    :TransfPix(obraz)
{
    setTransformacje(transfH, transfS, transfL);
}

TransfPixHSL::TransfPixHSL(ObrazRGB* obraz)
    :TransfPix(obraz)
{}

void TransfPixHSL::setTransformacje(int transfH, int transfS, int transfL)
{
    m_transfH = transfH;
    m_transfS = transfS;
    m_transfL = transfL;
}

void TransfPixHSL::zapiszZmianeObrazu()
{
    if(m_obraz != nullptr)
    {
        std::byte** kanalR = m_obraz->getKanalR();
        std::byte** kanalG = m_obraz->getKanalG();
        std::byte** kanalB = m_obraz->getKanalB();

        for(int i = 0; i < m_obraz->getSzerokosc(); i++)
        {
            for(int j = 0; j < m_obraz->getWysokosc(); j++)
            {
                int R = static_cast<int>(kanalR[i][j]);
                int G = static_cast<int>(kanalG[i][j]);
                int B = static_cast<int>(kanalB[i][j]);
                PixelRGB pRGB(R, G, B);

                //konwersja i dodanie transformacji
                PixelHSL pHSL = pRGB.konwertujDoHSL();

                pHSL.setH(pHSL.getH() + m_transfH);
                pHSL.setS(pHSL.getS() + m_transfS);
                pHSL.setL(pHSL.getL() + m_transfL);

                //powrot do RGB i wpisanie wartosci do pixelu
                pRGB = pHSL.konwertujDoRGB();

                kanalR[i][j] = static_cast<std::byte>(pRGB.getR());
                kanalG[i][j] = static_cast<std::byte>(pRGB.getG());
                kanalB[i][j] = static_cast<std::byte>(pRGB.getB());
            }
        }
    }
}

void TransfPixHSL::zerujTransformacje()
{
    m_transfH = 0;
    m_transfS = 0;
    m_transfL = 0;
}

//////////////////////////////
//TransfPixCMYK
//////////////////////////////

TransfPixCMYK::TransfPixCMYK(ObrazRGB* obraz, int transfC, int transfM, int transfY, int transfK)
    :TransfPix(obraz)
{
    setTransformacje(transfC, transfM, transfY, transfK);
}

TransfPixCMYK::TransfPixCMYK(ObrazRGB* obraz)
    :TransfPix(obraz)
{}

void TransfPixCMYK::setTransformacje(int transfC, int transfM, int transfY, int transfK)
{
    m_transfC = transfC;
    m_transfM = transfM;
    m_transfY = transfY;
    m_transfK = transfK;
}

void TransfPixCMYK::zapiszZmianeObrazu()
{
    if(m_obraz != nullptr)
    {
        std::byte** kanalR = m_obraz->getKanalR();
        std::byte** kanalG = m_obraz->getKanalG();
        std::byte** kanalB = m_obraz->getKanalB();

        for(int i = 0; i < m_obraz->getSzerokosc(); i++)
        {
            for(int j = 0; j < m_obraz->getWysokosc(); j++)
            {
                int R = static_cast<int>(kanalR[i][j]);
                int G = static_cast<int>(kanalG[i][j]);
                int B = static_cast<int>(kanalB[i][j]);
                PixelRGB pRGB(R, G, B);

                //konwersja i dodanie transformacji
                PixelCMYK pCMYK = pRGB.konwertujDoCMYK();

                pCMYK.setC(pCMYK.getC() + m_transfC);
                pCMYK.setM(pCMYK.getM() + m_transfM);
                pCMYK.setY(pCMYK.getY() + m_transfY);
                pCMYK.setK(pCMYK.getK() + m_transfK);

                //powrot do RGB i wpisanie wartosci do pixelu
                pRGB = pCMYK.konwertujDoRGB();

                kanalR[i][j] = static_cast<std::byte>(pRGB.getR());
                kanalG[i][j] = static_cast<std::byte>(pRGB.getG());
                kanalB[i][j] = static_cast<std::byte>(pRGB.getB());
            }
        }
    }
}

void TransfPixCMYK::zerujTransformacje()
{
    m_transfC = 0;
    m_transfM = 0;
    m_transfY = 0;
    m_transfK = 0;
}

//////////////////////////////
//TransfPixKlucz
//////////////////////////////

TransfPixKlucz::TransfPixKlucz(ObrazRGB* obraz, int transfR, int transfG, int transfB)
    :TransfPixRGB(obraz, transfR, transfG, transfB)
{
    m_kolorNieWybrany = false;
}

void TransfPixKlucz::setProgKluczowania(int prog)
{
    m_progKluczowaniaMemory = m_progKluczowania;
    m_progKluczowania = prog;
}

void TransfPixKlucz::zapiszZmianeObrazu()
{
    if(m_obraz != nullptr && m_kolorNieWybrany == false)
    {
        std::byte** kanalR = m_obraz->getKanalR();
        std::byte** kanalG = m_obraz->getKanalG();
        std::byte** kanalB = m_obraz->getKanalB();

        for(int i = 0; i < m_obraz->getSzerokosc(); i++)
        {
            for(int j = 0; j < m_obraz->getWysokosc(); j++)
            {
                int R = static_cast<int>(kanalR[i][j]);
                int G = static_cast<int>(kanalG[i][j]);
                int B = static_cast<int>(kanalB[i][j]);

                if(m_transfR - m_progKluczowania > R || R > m_transfR + m_progKluczowania ||
                    m_transfG - m_progKluczowania > G || G > m_transfG + m_progKluczowania ||
                    m_transfB - m_progKluczowania > B || B > m_transfB + m_progKluczowania)
                {
                    //wyszarzenie obrazu jesli wartosci kanalow nie znajduja sie w zakresie
                    int srednia = (int)((R + G + B) / 3.0);
                    kanalR[i][j] = static_cast<std::byte>(srednia);
                    kanalG[i][j] = static_cast<std::byte>(srednia);
                    kanalB[i][j] = static_cast<std::byte>(srednia);
                }
            }
        }
    }
}
