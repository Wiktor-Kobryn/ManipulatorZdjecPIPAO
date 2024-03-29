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
    ObrazRGB* zdjecieObecne = nullptr;
    void setGUI(MainWindow *ui = nullptr) {GUI = ui;}
    static Program*  getInstance(){
        if(object==nullptr) {
            Program* a = new Program();
            object = a;
            return object;
        }else return object;
    }
    ~Program(){
        if(object!=nullptr) delete object;
    }
private:
    MainWindow *GUI = nullptr;
    TransfPixRGB tRGB, tRGBmemory;
    TransfPixHSL tHSL, tHSLmemory, tKontrast, tKontrastMemory;
    TransfPixCMYK tCMYK, tCMYKmemory;
    TransfPixKlucz tKlucz;

    QVector<ObrazRGB*> historiaOperacji;
    int historiaIndex = 0;
    int historiaIndex_Max = 0;
    static Program* object;
    explicit Program(QObject *parent = nullptr);


signals:

private slots:
    void on_wybierzZdjecie();
    void on_mirrorX();
    void on_mirrorY();
    void on_negatyw();
    void on_test();

    void on_wyborKoloruKluczowania(QColor kolor);
    void on_zmianaProguKluczowania(int prog);
    void on_zastosujKluczowanie();

    void on_zmianaWartR(int R);
    void on_zmianaWartG(int G);
    void on_zmianaWartB(int B);

    void on_zmianaWartH(int H);
    void on_zmianaWartS(int S);
    void on_zmianaWartL(int L);
    void on_zmianaKontrastu(int kontrast);

    void on_zmianaWartC(int C);
    void on_zmianaWartM(int M);
    void on_zmianaWartY(int Y);
    void on_zmianaWartK(int K);

    void on_cofnij();
    void on_ponow();
    void on_cofnijDoZera();
    void dodaj_operacje();

    void ustaw_referencje();
};

#endif // PROGRAM_H
