#include "mainwindow.h"
#include "program.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Program mainProg;
    MainWindow window(nullptr, &mainProg);
    window.show();
    return a.exec();
}
