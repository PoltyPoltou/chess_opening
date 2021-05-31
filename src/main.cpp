#include "boardstate.h"
#include "mainwindow.h"
#include <iostream>
#include <qt5/QtWidgets/QApplication>
int main(int argc, char *argv[])
{
    chess::BoardState b;
    std::string buffer = "";
    while (buffer != "a1a1")
    {
        std::cout << b << std::endl;
        std::cin >> buffer;
        chess::Move mv(buffer);
        if (b.isLegal(mv))
        {
            b.playMove(mv);
        }
    }
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
