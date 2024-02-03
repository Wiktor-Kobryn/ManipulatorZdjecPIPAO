#ifndef PROGRAM_H
#define PROGRAM_H

#include <QObject>
#include <qdebug.h>

#include "obraz.h"
#include "QDialog"
#include "QFileDialog"
#include "transformacje.h"
#include "QVector"
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
    TransfPixRGB tRGB, tRGBmemory;
    TransfPixHSL tHSL, tHSLmemory;
    QVector<ObrazRGB*> historiaOperacji;
    int historiaIndex =0    ;
    int historiaIndex_Max = 0;

signals:

private slots:
    void on_wybierzZdjecie();
    void on_mirrorX();
    void on_mirrorY();
    void on_negatyw();
    void on_test();

    void on_zmianaWartR(int R);
    void on_zmianaWartG(int G);
    void on_zmianaWartB(int B);

    void on_zmianaWartH(int H);
    void on_zmianaWartS(int S);
    void on_zmianaWartL(int L);

    void on_cofnij();
    void on_ponow();

    void dodaj_operacje();
};

#endif // PROGRAM_H
