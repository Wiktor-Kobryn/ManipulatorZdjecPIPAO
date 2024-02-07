#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qdebug.h>
#include <obraz.h>
#include "QMessageBox.h"
#include <QFileDialog>

class Program;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, Program *app = nullptr);
    ~MainWindow();

signals:
    void wybierzZdjecie();
    void mirrorX();
    void mirrorY();
    void negatyw();
    void test();

    void wyborKoloruKluczowania(QColor kolor);
    void zmianaProguKluczowania(int prog);
    void zastosujKluczowanie();

    void zmianaWartR(int R);
    void zmianaWartG(int G);
    void zmianaWartB(int B);

    void zmianaWartH(int H);
    void zmianaWartS(int S);
    void zmianaWartL(int L);
    void zmianaKontrastu(int kontrast);

    void zmianaWartC(int C);
    void zmianaWartM(int M);
    void zmianaWartY(int Y);
    void zmianaWartK(int K);

    void cofnij();
    void ponow();
    void cofnijDoZera();

private slots:
    void on_BtnWybierzZdjecie_clicked();
    void on_BtnOdbicieOsiX_clicked();
    void on_BtnOdbicieOsiY_clicked();
    void on_BtnTest_clicked();   
    void on_SliderR_valueChanged(int value);
    void on_CbxR_valueChanged(int arg1);
    void on_SliderG_valueChanged(int value);
    void on_SliderB_valueChanged(int value);
    void on_CbxB_valueChanged(int arg1);
    void on_CbxG_valueChanged(int arg1);
    void on_SliderH_valueChanged(int value);
    void on_CbxH_valueChanged(int arg1);
    void on_SliderS_valueChanged(int value);
    void on_SliderL_valueChanged(int value);
    void on_CbxS_valueChanged(int arg1);
    void on_CbxL_valueChanged(int arg1);
    void on_BtnWindowColorPicker_clicked();
    void on_BtnNegatyw_clicked();
    void on_BtnCofnij_clicked();
    void on_BtnPonow_clicked();
    void on_SliderC_valueChanged(int value);
    void on_SliderM_valueChanged(int value);
    void on_SliderY_valueChanged(int value);
    void on_SliderK_valueChanged(int value);
    void on_CbxC_valueChanged(int arg1);
    void on_CbxM_valueChanged(int arg1);
    void on_CbxY_valueChanged(int arg1);
    void on_CbxK_valueChanged(int arg1);
    void on_SliderMoc_valueChanged(int value);
    void on_CbxMoc_valueChanged(int arg1);
    void on_HubTransfPodst_currentChanged(int index);
    void on_BtnZapiszZdjecie_clicked();
    void on_BtnCofnijWszystkie_clicked();
    void on_SliderR_sliderReleased();
    void on_SliderG_sliderReleased();
    void on_SliderB_sliderReleased(); 
    void on_SliderKontrast_sliderReleased();
    void on_CbxKontrast_valueChanged(int arg1);

    void on_SliderH_sliderReleased();

    void on_SliderS_sliderReleased();

    void on_SliderL_sliderReleased();

    void on_SliderC_sliderReleased();

    void on_SliderM_sliderReleased();

    void on_SliderY_sliderReleased();

    void on_SliderK_sliderReleased();

    void on_SliderH_sliderReleased();

    void on_SliderS_sliderReleased();

    void on_SliderL_sliderReleased();

    void on_SliderKontrast_sliderReleased();

    void on_SliderC_sliderReleased();

    void on_SliderM_sliderReleased();

    void on_SliderY_sliderReleased();

    void on_SliderK_sliderReleased();

private:
    Ui::MainWindow *ui = nullptr;
    Program *mainApp = nullptr;
    void odswiezZdjecie();
    void resetSliders();
};
#endif // MAINWINDOW_H
