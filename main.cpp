#include "mainwindow.h"
#include <QApplication>
#include <iostream>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    cout << "Hello World";
    return a.exec();
}

