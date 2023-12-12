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

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_BtnWybierzZdjecie_clicked()
{

    QString imagePath = QFileDialog::getOpenFileName(this, "Wybierz obraz", "", "Obrazy (*.png *.jpg *.jpeg *.bmp)");
    if (!imagePath.isEmpty()) {
        QPixmap image(imagePath);
        zdjecieRGB* ptr =  new zdjecieRGB(image);
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
        ui->LblObrazWe_2->setPixmap(this->mainApp->zdjecieObecne->topixmap().scaled(ui->LblObrazWe_2->width(),ui->LblObrazWe_2->height(), Qt::KeepAspectRatio));

}


void MainWindow::on_BtnOdbicieOsiY_clicked()
{
    emit MirrorY();
    if(this->mainApp->zdjecieObecne!=nullptr)
        ui->LblObrazWe_2->setPixmap(this->mainApp->zdjecieObecne->topixmap().scaled(ui->LblObrazWe_2->width(),ui->LblObrazWe_2->height(), Qt::KeepAspectRatio));

}

