#include "boardstate.h"
#include "mainwindow.h"
#include <iostream>
#include <qt5/QtWidgets/QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    chess::BoardState b;
    std::cout << b << std::endl;
    return a.exec();
}
