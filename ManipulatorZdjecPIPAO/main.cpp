#include "mainwindow.h"
#include "program.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow window(nullptr, Program::getInstance());
    window.show();
    return a.exec();
}
