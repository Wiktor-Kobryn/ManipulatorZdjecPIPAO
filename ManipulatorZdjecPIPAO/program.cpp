#include "program.h"
#include <QMessageBox>

void Program::on_WybierzZdjecie()
{
    qInfo() << "działa slot";
}

void Program::on_MirrorX(){
    ObrazRGB* temp = zdjecieObecne;
    if(zdjecieObecne!=nullptr)
        zdjecieObecne->odbijWzglOsiX();
    //if(temp!=nullptr) delete zdjecieObecne;


}

void Program::on_MirrorY(){

    ObrazRGB* temp = zdjecieObecne;
    if(zdjecieObecne!=nullptr)
        zdjecieObecne->odbijWzglOsiY();
    //if(temp!=nullptr) delete zdjecieObecne;
}

void Program::on_Test()
{
    TransfPixRGB tRGB(zdjecieObecne, 10, 10, 10);
    tRGB.zapiszZmianeObrazu();
}
