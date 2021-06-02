#include "mainwindow.h"
#include <iostream>
#include <qt5/QtWidgets/QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
