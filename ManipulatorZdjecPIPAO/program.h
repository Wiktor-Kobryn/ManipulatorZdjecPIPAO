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
    explicit Program(QObject *parent = nullptr);
    void setGUI(MainWindow *ui = nullptr) {GUI = ui;}

private:
    MainWindow *GUI = nullptr;
    TransfPixRGB tRGB;

signals:

private slots:
    void on_wybierzZdjecie();
    void on_mirrorX();
    void on_mirrorY();
    void on_test();
    void on_zmianaWartR(int R);
    void on_zmianaWartG(int G);
    void on_zmianaWartB(int B);
};

#endif // PROGRAM_H
