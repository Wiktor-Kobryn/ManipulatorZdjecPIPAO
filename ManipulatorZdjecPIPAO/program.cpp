#include "program.h"
#include <QMessageBox>

void Program::on_WybierzZdjecie()
{

}

void Program::on_MirrorX(){
    zdjecie* temp = zdjecieObecne;
    if(zdjecieObecne!=nullptr)
        zdjecieObecne = zdjecieObecne->obroc_horyzontalnie();
    //if(temp!=nullptr) delete zdjecieObecne;


}
void Program::on_MirrorY(){

    zdjecie* temp = zdjecieObecne;
    if(zdjecieObecne!=nullptr)
        zdjecieObecne = zdjecieObecne->obroc_wertykalnie();
    //if(temp!=nullptr) delete zdjecieObecne;
}
