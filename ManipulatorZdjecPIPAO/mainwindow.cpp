#include "mainwindow.h"
#include "program.h"
#include "ui_mainwindow.h"
#include "QColorDialog.h"

MainWindow::MainWindow(QWidget *parent, Program *app)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , mainApp(app)
{
    app->setGUI(this);
    ui->setupUi(this);

    connect(this, SIGNAL(wybierzZdjecie()), app, SLOT(on_wybierzZdjecie()));
    connect(this, SIGNAL(mirrorX()), app, SLOT(on_mirrorX()));
    connect(this, SIGNAL(mirrorY()), app, SLOT(on_mirrorY()));
    connect(this, SIGNAL(negatyw()), app, SLOT(on_negatyw()));

    connect(this, SIGNAL(test()), app, SLOT(on_test()));

    //RGB
    connect(this, SIGNAL(zmianaWartR(int)), app, SLOT(on_zmianaWartR(int)));
    connect(this, SIGNAL(zmianaWartG(int)), app, SLOT(on_zmianaWartG(int)));
    connect(this, SIGNAL(zmianaWartB(int)), app, SLOT(on_zmianaWartB(int)));

    //HSL
    connect(this, SIGNAL(zmianaWartH(int)), app, SLOT(on_zmianaWartH(int)));
    connect(this, SIGNAL(zmianaWartS(int)), app, SLOT(on_zmianaWartS(int)));
    connect(this, SIGNAL(zmianaWartL(int)), app, SLOT(on_zmianaWartL(int)));

    //CMYK
    connect(this, SIGNAL(zmianaWartC(int)), app, SLOT(on_zmianaWartC(int)));
    connect(this, SIGNAL(zmianaWartM(int)), app, SLOT(on_zmianaWartM(int)));
    connect(this, SIGNAL(zmianaWartY(int)), app, SLOT(on_zmianaWartY(int)));
    connect(this, SIGNAL(zmianaWartK(int)), app, SLOT(on_zmianaWartK(int)));

    connect(this, SIGNAL(cofnij()), app, SLOT(on_cofnij()));
    connect(this, SIGNAL(ponow()), app, SLOT(on_ponow()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_BtnWybierzZdjecie_clicked()
{
    //to powinno być w slocie programu a nie tu!!!!! - do przeniesienia


    emit wybierzZdjecie();
    ui->LblSciezkaWe->setText(QString::fromStdString(this->mainApp->zdjecieObecne->getSciezka()));
    odswiezZdjecie();
}

void MainWindow::on_BtnOdbicieOsiX_clicked()
{
    emit mirrorX();
    odswiezZdjecie();
}

void MainWindow::on_BtnOdbicieOsiY_clicked()
{
    emit mirrorY();
    odswiezZdjecie();
}

void MainWindow::on_BtnTest_clicked()
{
    emit test();
    odswiezZdjecie();
}

void MainWindow::odswiezZdjecie()
{

    if(this->mainApp->zdjecieObecne!=nullptr)
        ui->LblObrazPodglad->setPixmap(this->mainApp->zdjecieObecne->toPixmap().scaled(ui->LblObrazPodglad->width(),ui->LblObrazPodglad->height(), Qt::KeepAspectRatio));
}

void MainWindow::on_SliderR_valueChanged(int value)
{
    ui->CbxR->setValue(value);
    emit zmianaWartR(value);
    odswiezZdjecie();
}

void MainWindow::on_CbxR_valueChanged(int arg1)
{
    ui->SliderR->setValue(arg1);
}

void MainWindow::on_SliderG_valueChanged(int value)
{
    ui->CbxG->setValue(value);
    emit zmianaWartG(value);
    odswiezZdjecie();
}

void MainWindow::on_SliderB_valueChanged(int value)
{
    ui->CbxB->setValue(value);
    emit zmianaWartB(value);
    odswiezZdjecie();
}

void MainWindow::on_CbxB_valueChanged(int arg1)
{
    ui->SliderB->setValue(arg1);
}

void MainWindow::on_CbxG_valueChanged(int arg1)
{
    ui->SliderG->setValue(arg1);
}

void MainWindow::on_SliderH_valueChanged(int value)
{
    ui->CbxH->setValue(value);
    emit zmianaWartH(value);
    odswiezZdjecie();
}

void MainWindow::on_CbxH_valueChanged(int arg1)
{
    ui->SliderH->setValue(arg1);
}

void MainWindow::on_SliderS_valueChanged(int value)
{
    ui->CbxS->setValue(value);
    emit zmianaWartS(value);
    odswiezZdjecie();
}

void MainWindow::on_SliderL_valueChanged(int value)
{
    ui->CbxL->setValue(value);
    emit zmianaWartL(value);
    odswiezZdjecie();
}

void MainWindow::on_CbxS_valueChanged(int arg1)
{
    ui->SliderS->setValue(arg1);
}

void MainWindow::on_CbxL_valueChanged(int arg1)
{
    ui->SliderL->setValue(arg1);
}

void MainWindow::on_BtnDialogueColorPicker_clicked()
{
    //Zrobię że bierze ten pixel ale
    QColor color = QColorDialog::getColor(Qt::blue, this );
    if( color.isValid() )
       {
        QString a  = "background-color: rgb(";
                a+=QString::number(color.red()) + "," + QString::number(color.green())+"," + QString::number(color.blue()) +");";
        ui->LblKolorMaski_2->setStyleSheet(a);
       }
}

void MainWindow::on_BtnWindowColorPicker_clicked()
{

    //Dobre pytanie bo nie wiem co zrobic dalej - zbiera kolor ale zycie nie jest proste
    QColor color = QColorDialog::getColor(Qt::blue, this );
    if( color.isValid() )
       {
        QString a  = "background-color: rgb(";
                a+=QString::number(color.red()) + "," + QString::number(color.green())+"," + QString::number(color.blue()) +");";
        ui->LblKolorMaski_2->setStyleSheet(a);
       }
}

void MainWindow::on_BtnNegatyw_clicked()
{
    emit negatyw();
    odswiezZdjecie();

}

void MainWindow::on_BtnCofnij_clicked()
{
    emit cofnij();
    odswiezZdjecie();
}

void MainWindow::on_BtnPonow_clicked()
{
    emit ponow();
    odswiezZdjecie();
}

void MainWindow::on_SliderC_valueChanged(int value)
{
    ui->CbxC->setValue(value);
    emit zmianaWartC(value);
    odswiezZdjecie();
}

void MainWindow::on_SliderM_valueChanged(int value)
{
    ui->CbxM->setValue(value);
    emit zmianaWartM(value);
    odswiezZdjecie();
}

void MainWindow::on_SliderY_valueChanged(int value)
{
    ui->CbxY->setValue(value);
    emit zmianaWartY(value);
    odswiezZdjecie();
}

void MainWindow::on_SliderK_valueChanged(int value)
{
    ui->CbxK->setValue(value);
    emit zmianaWartK(value);
    odswiezZdjecie();
}

void MainWindow::on_CbxC_valueChanged(int arg1)
{
    ui->SliderC->setValue(arg1);
}

void MainWindow::on_CbxM_valueChanged(int arg1)
{
    ui->SliderM->setValue(arg1);
}

void MainWindow::on_CbxY_valueChanged(int arg1)
{
    ui->SliderY->setValue(arg1);
}

void MainWindow::on_CbxK_valueChanged(int arg1)
{
    ui->SliderK->setValue(arg1);
}

