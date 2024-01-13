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

    connect(this, SIGNAL(WybierzZdjecie()), app, SLOT(on_WybierzZdjecie()));
    connect(this, SIGNAL(MirrorX()), app, SLOT(on_MirrorX()));
    connect(this, SIGNAL(MirrorY()), app, SLOT(on_MirrorY()));
    connect(this, SIGNAL(Test()), app, SLOT(on_Test()));

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
      emit WybierzZdjecie();
}


void MainWindow::on_BtnOdbicieOsiX_clicked()
{
    emit MirrorX();
    if(this->mainApp->zdjecieObecne!=nullptr)
        ui->LblObrazPodglad->setPixmap(this->mainApp->zdjecieObecne->toPixmap().scaled(ui->LblObrazPodglad->width(),ui->LblObrazPodglad->height(), Qt::KeepAspectRatio));

}


void MainWindow::on_BtnOdbicieOsiY_clicked()
{
    emit MirrorY();
    if(this->mainApp->zdjecieObecne!=nullptr)
        ui->LblObrazPodglad->setPixmap(this->mainApp->zdjecieObecne->toPixmap().scaled(ui->LblObrazPodglad->width(),ui->LblObrazPodglad->height(), Qt::KeepAspectRatio));

}


void MainWindow::on_BtnTest_clicked()
{
    emit Test();
    //nie wiem czemu to się powtarza i jak działa ale trzeba to wydzielić na boga!
    if(this->mainApp->zdjecieObecne!=nullptr)
        ui->LblObrazPodglad->setPixmap(this->mainApp->zdjecieObecne->toPixmap().scaled(ui->LblObrazPodglad->width(),ui->LblObrazPodglad->height(), Qt::KeepAspectRatio));

}

