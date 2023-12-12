#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qfiledialog.h>
#include "manipulatorzdjec.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_BtnWybierzZdjecie_clicked()
{
   wczytywanieZdjec();
}


void MainWindow::wczytywanieZdjec(){
    QString imagePath = QFileDialog::getOpenFileName(this, "Wybierz obraz", "", "Obrazy (*.png *.jpg *.jpeg *.bmp)");
           if (!imagePath.isEmpty()) {
               QPixmap image(imagePath);
               if (!image.isNull()) {
                    zdjecieRGB zdjecie(image);
                   ui->GrViewZdjecieWe->setPixmap(image.scaled(300, 300, Qt::KeepAspectRatio));
                  //zdjecieRGB obrocone(zdjecie.obroc_horyzontalnie().doObrazu());
                 // ui->GrViewZdjecieWy->setPixmap(obrocone.doObrazu().scaled(300, 300, Qt::KeepAspectRatio));

               } else {
                   ui->GrViewZdjecieWe->setText("Nie można wczytać obrazu!");
               }
           }
}
