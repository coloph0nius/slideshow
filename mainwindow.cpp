#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDesktopWidget>
#include <QDir>
#include <QDebug>
#include <QStringList>
#include <QTimer>
#include <time.h>
#include <algorithm>


QStringList images;
QString dirpath="/media/usb0/";
int list[100000];



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	ui->ImageLabel->setStyleSheet("background-color:black;");
    picnum=0;

    //Get resolution
    QRect rec = QApplication::desktop()->screenGeometry();
    h = rec.height();
    w = rec.width();

    //Set path
    QDir dir;
    dir.setPath(dirpath);
    if (!dir.exists())
        qDebug()<<"Folder not found!";

    //Apply filter, show only jpg files
    QStringList filters;
    filters<<"*.jpg"<<"*.JPG";
    images=dir.entryList(filters);
    limit=images.size();

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

    //Start Timer which loads new image
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(newImage()));
    timer->setInterval(5000);
    timer->start();


}


void MainWindow::newImage()
{
    QString filename;
    QString imageno;
    imageno=images.at(list[picnum]);
    filename=dirpath;
    filename.append(imageno);
    QPixmap pixmap(filename);
    ui->ImageLabel->setPixmap(pixmap.scaled(w,h, Qt::KeepAspectRatio));
    picnum++;
    if (picnum>=limit)
        picnum=0;
}

MainWindow::~MainWindow()
{
    delete ui;
}
