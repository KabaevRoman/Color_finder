#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include <QPixmap>
#include <QMessageBox>
#include <QLabel>
#include <QFileDialog>
#include <QPushButton>
#include <iostream>
#include <QImage>
#include <QDebug>
#include <QList>
#include <QMap>
#include <QString>
#include <QPalette>
#include <stdlib.h>
#include <time.h>
#include <set>
#include <math.h>
#include <algorithm>
#include <QPainter>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void signal(QString filename);

private:
    Ui::MainWindow *ui;

    QImage result;


private slots:

    void but1slot();

    void on_pushButton_2_clicked();

    void main(QString filename);
};
#endif // MAINWINDOW_H
