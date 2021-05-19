#include <iostream>
#include <qt5/QtWidgets/QApplication>
#include "mainwindow.h"
int main(int argc, char *argv[])
{
    std::cout << "Hello world with Cmake !" << std::endl;
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
