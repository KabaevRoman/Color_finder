#include "mainwindow.h"

#include <QApplication>
#include <QFileDialog>
#include <QLabel>
#include <QPixmap>
#include <QRgb>
#include <QImage>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    return a.exec();
}
