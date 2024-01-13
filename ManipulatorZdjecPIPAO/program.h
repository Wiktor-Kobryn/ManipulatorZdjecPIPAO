#ifndef PROGRAM_H
#define PROGRAM_H

#include <QObject>
#include <qdebug.h>

#include "obraz.h"
#include "QDialog"
#include "QFileDialog"
#include "transformacje.h"
class MainWindow;

class Program : public QObject
{
    Q_OBJECT
public:
    ObrazRGB* zdjecieObecne;
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
    void on_Test();
};

#endif // PROGRAM_H
