#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QMessageBox>
#include <QLabel>
#include <QFileDialog>
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

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Get palette");
    QPushButton *button1 = new QPushButton(this);
    button1->setText("Выбрать изображение");
    ui->verticalLayout->addWidget(button1);

    connect(button1,SIGNAL(clicked()),this,SLOT(but1slot()));
    connect(this,&MainWindow::signal,this,&MainWindow::main);

}

class rgb
{
public:
    int red;
    int green;
    int blue;
    bool operator ==( const rgb& right)
    {
      if(this->red==right.red && this->green==right.green && this->blue==right.blue)
      {
        return true;
      }
      return false;
    }
    bool operator <(const rgb& right) const
    {
        return std::tie(this->red,this->green,this->blue) < std::tie(right.red,right.green,right.blue);
    }
};

void MainWindow::but1slot()
{
    QString filename = QFileDialog::getOpenFileName(this,tr("Open File"),"C://","*.jpg;*.png;*.jpeg");
    if(filename.isEmpty())
        return;

    else
        emit signal(filename);
}


void MainWindow::main(QString filename)
{
    QImage param(160,480,QImage::Format_ARGB32_Premultiplied);
    result = param;

    ui->label->setPixmap(QPixmap(filename));
    ui->label->setScaledContents(true);

    QImage img(filename);
    img = img.scaled(50, 25, Qt::KeepAspectRatio);
    QVector<rgb>pixels;
    std::set<rgb> uniquePixels;
    rgb pxl;
      for ( int row = 0; row < img.width() ; ++row )
        for ( int col = 0; col < img.height() ; ++col )
        {
            QColor clrCurrent( img.pixel( row, col ) );
                pxl.red = clrCurrent.red();
                pxl.green = clrCurrent.green();
                pxl.blue = clrCurrent.blue();
                pixels.push_back(pxl);
                uniquePixels.insert(pxl);
        }

    QVector<rgb>chosen;

    srand(time(NULL));

    for(int k = 0; k < 6; ++k)
    {
        std::set<rgb>::iterator it = uniquePixels.begin(); //итератор для сета
        int random_increment = rand()%uniquePixels.size(); //рандомим число не превышающее кол-во элементов сета
        for(int i = 0; i < random_increment; i++)
        {
            it++; //увеличиваем итератор до этого числа
        }
        chosen.push_back(*it); //засовываем наш рандомный пиксель в chosen
    }

    //кластеринг

    int iter_count = 0;  //счетчик  количества итераций
    int iter_max = 100;

    while(iter_count != iter_max)
    {
        for(int i = 0; i < pixels.size(); i++)
        {
           int* distances_array = new int[chosen.size()];
           for(int j = 0; j < chosen.size(); j++)
           {
               distances_array[j] = sqrt(pow((pixels[i].red-chosen[j].red),2) + pow((pixels[i].green-chosen[j].green),2) + pow((pixels[i].blue-chosen[j].blue),2) );
           }
           int minimal_distance = *(std::min_element(distances_array, distances_array+chosen.size()));
           int closest_center = std::distance(distances_array, std::find(distances_array,distances_array+chosen.size(), minimal_distance));
           //пересчитываем центры
           chosen[closest_center].red = (chosen[closest_center].red+pixels[i].red)/2;
           chosen[closest_center].green = (chosen[closest_center].green+pixels[i].green)/2;
           chosen[closest_center].blue = (chosen[closest_center].blue+pixels[i].blue)/2;

           delete[] distances_array;
        }

        iter_count++;

    }

    QColor colors[6];
    for(int i = 0;i < 6; ++i)
        colors[i].setRgb(chosen[i].red, chosen[i].green,chosen[i].blue);


    QPainter painter(&result);
    for (int i = 0; i < 6; ++i)
    {
        painter.fillRect(0,i*80,160,80,colors[i]);
    }
    for (int i = 1; i <= 6; ++i)
    {
        QColor temp;
        temp.setRgb(abs(255-chosen[i-1].red),abs(255-chosen[i-1].green),abs(255-chosen[i-1].blue));//(255-chosen[i].red,255-chosen[i].green,255-chosen[i].blue);
        painter.setPen(temp);
        painter.drawText(60,i*80-35, colors[i-1].name().toUpper());
    }
    ui->label_9->setPixmap(QPixmap::fromImage(result));


}


void MainWindow::on_pushButton_2_clicked()
{
    QString fileSavename = QFileDialog::getSaveFileName(this,tr("Save File"),"C://result.png ");;
    if(fileSavename.isEmpty())
        return;
    result.save(fileSavename);
}

MainWindow::~MainWindow()
{
    delete ui;
}




