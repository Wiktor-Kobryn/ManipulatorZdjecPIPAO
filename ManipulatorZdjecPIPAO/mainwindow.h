#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#pragma once
#include <QMainWindow>
#include <qdebug.h>
#include <manipulatorzdjec.h>

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

private slots:
    void on_BtnWybierzZdjecie_clicked();

private:
    Ui::MainWindow *ui = nullptr;
    Program *mainApp = nullptr;
};
#endif // MAINWINDOW_H
