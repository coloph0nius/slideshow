#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    int h;
    int w;
    int picnum;
    QString filename;
    QString imageno;
    QRect rec;
    QStringList images;

private slots:
   void newImage();
};

#endif // MAINWINDOW_H
