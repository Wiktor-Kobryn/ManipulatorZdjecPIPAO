#pragma once
#ifndef PROGRAM_H
#define PROGRAM_H

#include <QObject>
#include <qdebug.h>
#include "manipulatorzdjec.h"
#include "QDialog"
#include "QFileDialog"
class MainWindow;

class Program : public QObject
{
    Q_OBJECT
public:
    zdjecie* zdjecieObecne;
    explicit Program(QObject *parent = nullptr)
        :QObject (parent) {}
    void setGUI(MainWindow *ui = nullptr) {GUI = ui;}

private:
    MainWindow *GUI = nullptr;

signals:

private slots:
    void on_WybierzZdjecie();
    void on_MirrorX();
    void on_MirrorY();

};

#endif // PROGRAM_H
