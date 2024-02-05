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

    connect(this, SIGNAL(wyborKoloruKluczowania(QColor)), app, SLOT(on_wyborKoloruKluczowania(QColor)));
    connect(this, SIGNAL(zmianaProguKluczowania(int)), app, SLOT(on_zmianaProguKluczowania(int)));
    connect(this, SIGNAL(zastosujKluczowanie()), app, SLOT(on_zastosujKluczowanie()));
    connect(this, SIGNAL(cofnijDoZera()), app, SLOT(on_cofnijDoZera()));

    connect(this, SIGNAL(test()), app, SLOT(on_test()));

    //RGB
    connect(this, SIGNAL(zmianaWartR(int)), app, SLOT(on_zmianaWartR(int)));
    connect(this, SIGNAL(zmianaWartG(int)), app, SLOT(on_zmianaWartG(int)));
    connect(this, SIGNAL(zmianaWartB(int)), app, SLOT(on_zmianaWartB(int)));

    //HSL
    connect(this, SIGNAL(zmianaWartH(int)), app, SLOT(on_zmianaWartH(int)));
    connect(this, SIGNAL(zmianaWartS(int)), app, SLOT(on_zmianaWartS(int)));
    connect(this, SIGNAL(zmianaWartL(int)), app, SLOT(on_zmianaWartL(int)));
    connect(this, SIGNAL(zmianaKontrastu(int)), app, SLOT(on_zmianaKontrastu(int)));

    //CMYK
    connect(this, SIGNAL(zmianaWartC(int)), app, SLOT(on_zmianaWartC(int)));
    connect(this, SIGNAL(zmianaWartM(int)), app, SLOT(on_zmianaWartM(int)));
    connect(this, SIGNAL(zmianaWartY(int)), app, SLOT(on_zmianaWartY(int)));
    connect(this, SIGNAL(zmianaWartK(int)), app, SLOT(on_zmianaWartK(int)));

    connect(this, SIGNAL(cofnij()), app, SLOT(on_cofnij()));
    connect(this, SIGNAL(ponow()), app, SLOT(on_ponow()));

    //Blokada Hubu

    ui->HubTransfPodst->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_BtnWybierzZdjecie_clicked()
{
    resetSliders();
    emit wybierzZdjecie();
    if(mainApp->zdjecieObecne!=nullptr){
        //brakuje wyswietlania samej nazwy pliku i rozmiaru
        QString sciezka= QString::fromStdString(this->mainApp->zdjecieObecne->getSciezka());
        ui->LblSciezkaWe->setText("sciezka: " + sciezka);

        //nie jest to najoptymalniejsze zasobowo, ale programistycznie najszybsze
        QStringList nazwa = sciezka.split('/');
        ui->LblNazwaWe->setText("nazwa:"+ nazwa.last());

        ui->LblRozmiarWe->setText("rozmiar:" + QString::number(mainApp->zdjecieObecne->getSzerokosc()) + "x" +QString::number(mainApp->zdjecieObecne->getWysokosc()));
        //Ustawienie podgladu
        ui->LblObrazWe->setPixmap(mainApp->zdjecieObecne->toPixmap());
        odswiezZdjecie();
    }
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
//Zostawmy stare slidery to ustawiania value na boxach
void MainWindow::on_SliderR_valueChanged(int value)
{
    ui->CbxR->setValue(value);
}

void MainWindow::on_SliderG_valueChanged(int value)
{
    ui->CbxG->setValue(value);

}

void MainWindow::on_SliderB_valueChanged(int value)
{
    ui->CbxB->setValue(value);

}

void MainWindow::on_CbxR_valueChanged(int arg1)
{
    ui->SliderR->setValue(arg1);
}


void MainWindow::on_CbxB_valueChanged(int arg1)
{
    ui->SliderB->setValue(arg1);
}

void MainWindow::on_CbxG_valueChanged(int arg1)
{
    ui->SliderG->setValue(arg1);
}

void MainWindow::on_CbxH_valueChanged(int arg1)
{
    ui->SliderH->setValue(arg1);
}

void MainWindow::on_SliderH_valueChanged(int value)
{
    ui->CbxH->setValue(value);
    emit zmianaWartH(value);
    odswiezZdjecie();
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

void MainWindow::on_BtnWindowColorPicker_clicked()
{
    QColor color = QColorDialog::getColor(Qt::blue, this);
    if( color.isValid() )
    {
        QString a  = "background-color: rgb(";
        a+=QString::number(color.red()) + "," + QString::number(color.green())+"," + QString::number(color.blue()) +");";
        ui->LblKolorMaski_2->setStyleSheet(a);

        emit wyborKoloruKluczowania(color);
        emit zastosujKluczowanie();
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

void MainWindow::on_SliderMoc_valueChanged(int value)
{
    ui->CbxMoc->setValue(value);
    emit zmianaProguKluczowania(value);
    emit zastosujKluczowanie();
    odswiezZdjecie();
}

void MainWindow::on_CbxMoc_valueChanged(int arg1)
{
    ui->SliderMoc->setValue(arg1);
}

void MainWindow::on_HubTransfPodst_currentChanged(int index)
{
    if(this->mainApp->zdjecieObecne==nullptr && index != 0){
        QMessageBox error ;
        ui->HubTransfPodst->setCurrentIndex(0);
        error.setText("WYBIERZ OBRAZ!");
        error.exec();
    }

}


void MainWindow::on_BtnZapiszZdjecie_clicked()
{
    //Przenieść to do Program
        QString fileName = QFileDialog::getSaveFileName(nullptr, "Zapisz obraz", "", "Obrazy PNG (*.png)");

        if (!fileName.isEmpty()) {
            if (!fileName.toLower().endsWith(".png")) {
                fileName += ".png";
            }
            if(mainApp->zdjecieObecne!=nullptr){
                if (mainApp->zdjecieObecne->toPixmap().save(fileName, "PNG")) {
                    QMessageBox::information(nullptr, "Zapisano", "Obraz został pomyślnie zapisany do pliku.");
                } else {
                    QMessageBox::warning(nullptr, "Błąd", "Wystąpił błąd podczas zapisywania obrazu do pliku.");
                }
            }
        }
}

void MainWindow::resetSliders(){
    ui->SliderS->setValue(0);
    ui->SliderB->setValue(0);
    ui->SliderC->setValue(0);
    ui->SliderG->setValue(0);
    ui->SliderH->setValue(0);
    ui->SliderK->setValue(0);
    ui->SliderKontrast->setValue(0);
    ui->SliderL->setValue(0);
    ui->SliderM->setValue(0);
    ui->SliderY->setValue(0);
    ui->SliderR->setValue(0);
    ui->SliderMoc->setValue(100);
}

void MainWindow::on_BtnCofnijWszystkie_clicked()
{
    resetSliders();
    emit cofnijDoZera();
      odswiezZdjecie();
}
//Zmiany slotu Sliderow

void MainWindow::on_SliderR_sliderReleased()
{
    int value = ui->SliderR->value();
    ui->CbxR->setValue(value);
    emit zmianaWartR(value);
    odswiezZdjecie();
}

void MainWindow::on_SliderG_sliderReleased()
{
    int value = ui->SliderG->value();
    ui->CbxG->setValue(value);
    emit zmianaWartG(value);
    odswiezZdjecie();
}

void MainWindow::on_SliderB_sliderReleased()
{
    int value = ui->SliderB->value();
    ui->CbxB->setValue(value);
    emit zmianaWartB(value);
    odswiezZdjecie();
}

void MainWindow::on_SliderKontrast_sliderReleased()
{
    int value = ui->SliderKontrast->value();
    ui->CbxKontrast->setValue(value);
    emit zmianaKontrastu(value);
    odswiezZdjecie();
}

void MainWindow::on_CbxKontrast_valueChanged(int arg1)
{
    ui->SliderKontrast->setValue(arg1);
}

