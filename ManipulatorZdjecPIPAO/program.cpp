#include "program.h"
#include <QMessageBox>

Program::Program(QObject *parent)
    :QObject (parent)
{}

void Program::on_wybierzZdjecie()
{
    //tu implementacja dodawania zdjęcia z pliku!!!

    //dodanie referencji do obrazu dla transformacji
    tRGB.setObraz(zdjecieObecne);
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

void Program::on_test()
{
    PixelRGB pr(12, 250, 67);
    PixelHSL ph = pr.konwertujDoHSL();
    std::cerr << "RGB(12,250,67)\tHSL(" << ph.getH() << "," << ph.getS() << "," << ph.getL() << ")\n";
    PixelHSL ph2(46, 17, 80);
    pr = ph2.konwertujDoRGB();
    std::cerr << "HSL(46,17,80)\tRGB(" << pr.getR() << "," << pr.getG() << "," << pr.getB() << ")\n";
}
