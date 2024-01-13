#include "program.h"
#include <QMessageBox>

Program::Program(QObject *parent)
    :QObject (parent)
{
    tRGB = TransfPixRGB(zdjecieObecne);
}

void Program::on_wybierzZdjecie()
{
    //tu implementacja dodawania zdjęcia z pliku!!!

    qInfo() << "działa slot";
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
    /*
    tRGB.setTransfR(R);
    std::cerr << "transf: " << tRGB.getTransfR() << ", " << tRGB.getObraz() << "\n";
    tRGB.zapiszTransfKanaluR();*/

    TransfPixRGB _tRGB(zdjecieObecne, R, 0, 0);
    _tRGB.zapiszZmianeObrazu();
}

void Program::on_zmianaWartG(int G)
{
    tRGB.setTransfG(G);
    tRGB.zapiszTransfKanaluG();
}

void Program::on_zmianaWartB(int B)
{
    tRGB.setTransfB(B);
    tRGB.zapiszTransfKanaluB();
}

void Program::on_test()
{
    TransfPixRGB _tRGB(zdjecieObecne, 10, 10, 10);
    _tRGB.zapiszZmianeObrazu();
}
