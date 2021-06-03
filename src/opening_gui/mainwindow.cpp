#include "mainwindow.h"
#include "ui/ui_mainwindow.h"

#include <QPushButton>
#include <iostream>
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::OnButtonPress()
{
    std::cout << "YOU PRESSED A BUTTON" << std::endl;
}