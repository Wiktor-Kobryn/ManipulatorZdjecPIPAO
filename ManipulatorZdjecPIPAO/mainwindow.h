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
    void WybierzZdjecie();
    void MirrorX();
    void MirrorY();
    void Test();

private slots:
    void on_BtnWybierzZdjecie_clicked();
    void on_BtnOdbicieOsiX_clicked();
    void on_BtnOdbicieOsiY_clicked();
    void on_BtnTest_clicked();

private:
    Ui::MainWindow *ui = nullptr;
    Program *mainApp = nullptr;
};
#endif // MAINWINDOW_H
