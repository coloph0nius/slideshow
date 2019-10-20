#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDesktopWidget>
#include <QDir>
#include <QStringList>
#include <QTimer>



static QString dirpath="F:/Bilder/test/";


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	ui->ImageLabel->setStyleSheet("background-color:black;");

    picnum = 0; //because some old g++ variants won't accept declaring variables in the header file
    //Get resolution
    rec = QApplication::desktop()->screenGeometry(); //this creates a rectangle over the whole screen
    h = rec.height(); //get the height from the fullscreen rectangle
    w = rec.width(); //get the width from the fullscreen rectangle

    //Set path
    QDir dir;
    dir.setPath(dirpath);
    if (!dir.exists())
    {
        QCoreApplication::quit();
    }

    //Apply filter, show only jpg files
    QStringList filters;
    filters<<"*.jpg"<<"*.JPG";
    images = dir.entryList(filters); //populate images array with the picture names in the folder

    //Start Timer which loads new image every 5 seconds
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(newImage()));
    timer->setInterval(5000);
    timer->start();
}


void MainWindow::newImage()
{
    filename = dirpath+images.at(picnum); //build the path to the displayed image
    QPixmap pixmap(filename); //create a pixmap with the displayed image
    ui->ImageLabel->setPixmap(pixmap.scaled(w,h, Qt::KeepAspectRatio)); //scale image to screen resolution, keep aspect ratio
    picnum++; //next image
    if (picnum >= images.size()) //if we reached the end, start from the beginning
    {
        picnum = 0;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}



/*
    #include <time.h>
    #include <algorithm>

    int list[100000]; //only used for random order
    //Create a random picture order
    srand(time(0));
    int randpiclist[limit];
    for (int i=0;i<limit;i++)
        randpiclist[i]=i;
    std::random_shuffle(&randpiclist[0], &randpiclist[limit]);
    for (int i=0; i<limit;i++)
        list[i]=randpiclist[i];

    //for(int i=0; i<limit;i++)qDebug()<<"first occurance"<<list[i];
    //qDebug()<<"sizeof randpiclist and list:"<<limit;
    //for(int i=0; i<limit;i++) {qDebug()<<images.at(i);}
*/
