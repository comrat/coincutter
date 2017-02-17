#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "circlerecognizer.h"
#include "filters.h"

#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap image("./1.jpg");
    image = image.scaled(ui->label->width(), ui->label->height(), Qt::KeepAspectRatio);

	//CircleRecognizer recognizer;
    //ui->label->setPixmap(QPixmap::fromImage(recognizer.Binarize(image.toImage())));
	//ui->label->setPixmap(QPixmap::fromImage(recognizer.CannyFilter(image.toImage())));
	//ui->label->setPixmap(QPixmap::fromImage(Filters::Canny(image.toImage())));

	ui->label->setPixmap(QPixmap::fromImage(Filters::Canny(image.toImage())));
	//ui->label->setPixmap(QPixmap::fromImage(Filters::Sobel(image.toImage())));
}

MainWindow::~MainWindow()
{
    delete ui;
}
