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
    QPixmap pixmap;

private slots:
   void newImage();
   void errorImage();
};

#endif // MAINWINDOW_H
