#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qdebug.h>
#include <obraz.h>

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
    void test();
    void zmianaWartR(int R);
    void zmianaWartG(int G);
    void zmianaWartB(int B);

private slots:
    void on_BtnWybierzZdjecie_clicked();
    void on_BtnOdbicieOsiX_clicked();
    void on_BtnOdbicieOsiY_clicked();
    void on_BtnTest_clicked();   
    void on_SliderR_valueChanged(int value);
    void on_CbxR_valueChanged(int arg1);

private:
    Ui::MainWindow *ui = nullptr;
    Program *mainApp = nullptr;
    void odswiezZdjecie();
};
#endif // MAINWINDOW_H
