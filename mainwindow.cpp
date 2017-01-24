#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "PixelFormat.h"
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap image("./1.jpg");
    image = image.scaled(ui->label->width(), ui->label->height(), Qt::KeepAspectRatio);
    ui->label->setPixmap(image);


}

MainWindow::~MainWindow()
{
    delete ui;
}
