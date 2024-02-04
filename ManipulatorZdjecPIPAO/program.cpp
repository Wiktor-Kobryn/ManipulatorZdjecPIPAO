#include "program.h"
#include <QMessageBox>

Program::Program(QObject *parent)
    :QObject (parent)
{}

void Program::on_wybierzZdjecie()
{
    QString imagePath = QFileDialog::getOpenFileName(nullptr, "Wybierz obraz", "", "Obrazy (*.png)");

    //tu implementacja dodawania zdjęcia z pliku!!!
    if (!imagePath.isEmpty())
    {
        QPixmap image(imagePath);
        ObrazRGB* ptr =  new ObrazRGB(image);
        this->zdjecieObecne= ptr;
        this->zdjecieObecne->setSciezka(imagePath.toStdString());
    }

    //dodanie referencji do obrazu dla transformacji
    tRGB.setObraz(zdjecieObecne);
    tHSL.setObraz(zdjecieObecne);
    tCMYK.setObraz(zdjecieObecne);
}

void Program::dodaj_operacje()
{
    //Coś jeszcze nie dziala - tak jakby image 0 jest obecnym, dziwne//
    if(historiaIndex<historiaIndex_Max)
    {
        //Tu trzeba trzeba zerować hsitorie do punktu HistoriaIndex

        historiaOperacji.resize(historiaIndex+1);
        historiaIndex_Max=historiaIndex;
    }

    ObrazRGB* a = new ObrazRGB(this->zdjecieObecne->toPixmap());
    historiaOperacji.push_back(a);
    historiaIndex++;
    historiaIndex_Max++;
}

void Program::on_mirrorX()
{

    dodaj_operacje();
    if(zdjecieObecne!=nullptr)
        zdjecieObecne->odbijWzglOsiX();
}

void Program::on_mirrorY()
{
    dodaj_operacje();
    if(zdjecieObecne!=nullptr)
        zdjecieObecne->odbijWzglOsiY();
}

void Program::on_negatyw()
{
    dodaj_operacje();
    if(zdjecieObecne!=nullptr)
        zdjecieObecne->negatywowanie();
}

void Program::on_zmianaWartR(int R)
{
    dodaj_operacje();
    if(zdjecieObecne != nullptr)
    {
        int przesuniecie = R - tRGBmemory.getTransfR();

        tRGB.setTransfR(przesuniecie);
        tRGB.zapiszTransfKanaluR();

        tRGBmemory.setTransfR(R);
    }
}

void Program::on_zmianaWartG(int G)
{
    dodaj_operacje();
    if(zdjecieObecne != nullptr)
    {
        int przesuniecie = G - tRGBmemory.getTransfG();

        tRGB.setTransfG(przesuniecie);
        tRGB.zapiszTransfKanaluG();

        tRGBmemory.setTransfG(G);
    }
}

void Program::on_zmianaWartB(int B)
{
    dodaj_operacje();
    if(zdjecieObecne != nullptr)
    {
        int przesuniecie = B - tRGBmemory.getTransfB();

        tRGB.setTransfB(przesuniecie);
        tRGB.zapiszTransfKanaluB();

        tRGBmemory.setTransfB(B);
    }
}

void Program::on_zmianaWartH(int H)
{
    dodaj_operacje();
    if(zdjecieObecne != nullptr)
    {
        int przesuniecie = H - tHSLmemory.getTransfH();

        tHSL.setTransfH(przesuniecie);
        tHSL.zapiszZmianeObrazu();

        tHSLmemory.setTransfH(H);
    }
}

void Program::on_zmianaWartS(int S)
{
    dodaj_operacje();
    if(zdjecieObecne != nullptr)
    {
        int przesuniecie = S - tHSLmemory.getTransfS();

        tHSL.setTransfS(przesuniecie);
        tHSL.zapiszZmianeObrazu();

        tHSLmemory.setTransfS(S);
    }
}

void Program::on_zmianaWartL(int L)
{
    dodaj_operacje();
    if(zdjecieObecne != nullptr)
    {
        int przesuniecie = L - tHSLmemory.getTransfL();

        tHSL.setTransfL(przesuniecie);
        tHSL.zapiszZmianeObrazu();

        tHSLmemory.setTransfL(L);
    }
}

void Program::on_test()
{
    PixelRGB pr(12, 250, 67);
    PixelHSL ph = pr.konwertujDoHSL();
    std::cerr << "RGB(12,250,67)\tHSL(" << ph.getH() << "," << ph.getS() << "," << ph.getL() << ")\n";
    PixelHSL ph2(46, 17, 80);
    pr = ph2.konwertujDoRGB();
    std::cerr << "HSL(46,17,80)\tRGB(" << pr.getR() << "," << pr.getG() << "," << pr.getB() << ")\n";

    PixelRGB prg(123, 12, 76);
    PixelCMYK pc = prg.konwertujDoCMYK();
    std::cerr << "RGB(123,12,76)\tCMYK(" << pc.getC() << "," << pc.getM() << "," << pc.getY() << "," << pc.getK() << ")\n";
    PixelCMYK pc2(17, 89, 71, 3);
    prg = pc2.konwertujDoRGB();
    std::cerr << "CMYK(17,89,71,3)\tRGB(" << prg.getR() << "," << prg.getG() << "," << prg.getB() << ")\n";
}

void Program::on_cofnij()
{
    if(historiaIndex > 1)
    {
        this->historiaIndex--;
        this->zdjecieObecne = historiaOperacji[historiaIndex];
        tRGB.setObraz(zdjecieObecne);
        tHSL.setObraz(zdjecieObecne);
        qDebug() << historiaIndex;

    }
}

void Program::on_ponow()
{
    if(historiaIndex+1 < historiaIndex_Max)
    {
        this->historiaIndex++;
        this->zdjecieObecne = historiaOperacji[historiaIndex];
        tRGB.setObraz(zdjecieObecne);
        tHSL.setObraz(zdjecieObecne);
        qDebug() << historiaIndex;
    }
}

void Program::on_zmianaWartC(int C)
{
    dodaj_operacje();
    if(zdjecieObecne != nullptr)
    {
        int przesuniecie = C - tCMYKmemory.getTransfC();

        tCMYK.setTransfC(przesuniecie);
        tCMYK.zapiszZmianeObrazu();

        tCMYKmemory.setTransfC(C);
    }
}

void Program::on_zmianaWartM(int M)
{
    dodaj_operacje();
    if(zdjecieObecne != nullptr)
    {
        int przesuniecie = M - tCMYKmemory.getTransfM();

        tCMYK.setTransfM(przesuniecie);
        tCMYK.zapiszZmianeObrazu();

        tCMYKmemory.setTransfM(M);
    }
}

void Program::on_zmianaWartY(int Y)
{
    dodaj_operacje();
    if(zdjecieObecne != nullptr)
    {
        int przesuniecie = Y - tCMYKmemory.getTransfY();

        tCMYK.setTransfY(przesuniecie);
        tCMYK.zapiszZmianeObrazu();

        tCMYKmemory.setTransfY(Y);
    }
}

void Program::on_zmianaWartK(int K)
{
    dodaj_operacje();
    if(zdjecieObecne != nullptr)
    {
        int przesuniecie = K - tCMYKmemory.getTransfK();

        tCMYK.setTransfK(przesuniecie);
        tCMYK.zapiszZmianeObrazu();

        tCMYKmemory.setTransfK(K);
    }
}

void Program::on_wyborKoloruKluczowania(QColor kolor)
{
    int R = 0, G = 0, B = 0;
    kolor.getRgb(&R, &G, &B);

    int prog = tKlucz.getProgKluczowania();
    tKlucz = TransfPixKlucz(zdjecieObecne, R, G, B);
    tKlucz.setProgKluczowania(prog);
}

void Program::on_zmianaProguKluczowania(int prog)
{
    tKlucz.setProgKluczowania(prog);
}

void Program::on_zastosujKluczowanie()
{
    if(zdjecieObecne != nullptr)
    {
        dodaj_operacje();
        tKlucz.zapiszZmianeObrazu();
    }
}
