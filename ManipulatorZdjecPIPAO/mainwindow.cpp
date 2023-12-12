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
        zdjecieRGB imgRGB(image);
        if (!image.isNull()) {
          ui->GrViewZdjecieWe->setPixmap(image.scaled(300, 300, Qt::KeepAspectRatio));
        } else {
          ui->GrViewZdjecieWe->setText("Nie można wczytać obrazu!");
        }
        ui->GrViewZdjecieWy->setPixmap(imgRGB.obroc_wertykalnie()->topixmap().scaled(300, 300, Qt::KeepAspectRatio));
    }
      emit WybierzZdjecie();
}

