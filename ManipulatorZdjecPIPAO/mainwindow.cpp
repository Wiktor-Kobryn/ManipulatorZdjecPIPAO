#include "mainwindow.h"
#include "program.h"
#include "ui_mainwindow.h"

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
    connect(this, SIGNAL(test()), app, SLOT(on_test()));

    connect(this, SIGNAL(zmianaWartR(int)), app, SLOT(on_zmianaWartR(int)));
    connect(this, SIGNAL(zmianaWartG(int)), app, SLOT(on_zmianaWartG(int)));
    connect(this, SIGNAL(zmianaWartB(int)), app, SLOT(on_zmianaWartB(int)));

    connect(this, SIGNAL(zmianaWartH(int)), app, SLOT(on_zmianaWartH(int)));
    connect(this, SIGNAL(zmianaWartS(int)), app, SLOT(on_zmianaWartS(int)));
    connect(this, SIGNAL(zmianaWartL(int)), app, SLOT(on_zmianaWartL(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_BtnWybierzZdjecie_clicked()
{
    //to powinno być w slocie programu a nie tu!!!!! - do przeniesienia

    QString imagePath = QFileDialog::getOpenFileName(this, "Wybierz obraz", "", "Obrazy (*.png)");
    if (!imagePath.isEmpty()) {
        QPixmap image(imagePath);
        ObrazRGB* ptr =  new ObrazRGB(image);
        this->mainApp->zdjecieObecne= ptr;

        if (!image.isNull()) {
          ui->LblObrazWe->setPixmap(image.scaled(ui->LblObrazWe->width(), ui->LblObrazWe->height(), Qt::KeepAspectRatio));
          ui->LblSciezkaWe->setText(imagePath);

        } else {
          ui->LblObrazWe->setText("Nie można wczytać obrazu!");
        }
    }
      emit wybierzZdjecie();

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

