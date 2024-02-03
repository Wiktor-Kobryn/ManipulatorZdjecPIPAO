#include "program.h"
#include <QMessageBox>

Program::Program(QObject *parent)
    :QObject (parent)
{}

void Program::on_wybierzZdjecie()
{
    QString imagePath = QFileDialog::getOpenFileName(nullptr, "Wybierz obraz", "", "Obrazy (*.png)");

    //tu implementacja dodawania zdjęcia z pliku!!!
    if (!imagePath.isEmpty()) {
        QPixmap image(imagePath);
        ObrazRGB* ptr =  new ObrazRGB(image);
        this->zdjecieObecne= ptr;
        this->zdjecieObecne->setSciezka(imagePath.toStdString());

    }
    //dodanie referencji do obrazu dla transformacji
    tRGB.setObraz(zdjecieObecne);
    tHSL.setObraz(zdjecieObecne);
}

void Program::on_mirrorX()
{
    if(zdjecieObecne!=nullptr)
        zdjecieObecne->odbijWzglOsiX();
}

void Program::on_mirrorY()
{
    if(zdjecieObecne!=nullptr)
        zdjecieObecne->odbijWzglOsiY();
}

void Program::on_zmianaWartR(int R)
{
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
}
