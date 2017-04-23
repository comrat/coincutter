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

	using namespace filters;

	CircleRecognizer recognizer;
	QImage original = image.toImage();
	QImage img = original;
	img = Canny(img);
	Circles circles = recognizer.FindCircles(img);
	for (Circles::iterator it = circles.begin(); it != circles.end(); ++it)
		DrawCircle(original, *it);

	ui->label->setPixmap(QPixmap::fromImage(original));
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::PutPixel(QImage& image, int x, int y)
{
	if (x < 0 || y < 0 || x >= image.width() || y >= image.height())
		return;
	image.setPixel(x, y, QColor(255, 0, 0).rgba());
}


void MainWindow::DrawCircle(QImage& image, const Circle& circle)
{
	int x0 = circle.x;
	int y0 = circle.y;
	int x = circle.radius;
	int y = 0;
	int err = 0;
	int total = 0;
	int match = 0;

	while (x >= y) {
		PutPixel(image, x0 + x, y0 + y);
		PutPixel(image, x0 + y, y0 + x);
		PutPixel(image, x0 - y, y0 + x);
		PutPixel(image, x0 - x, y0 + y);
		PutPixel(image, x0 - x, y0 - y);
		PutPixel(image, x0 - y, y0 - x);
		PutPixel(image, x0 + y, y0 - x);
		PutPixel(image, x0 + x, y0 - y);

		if (err <= 0) {
			y += 1;
			err += 2 * y + 1;
		}
		if (err > 0) {
			x -= 1;
			err -= 2 * x + 1;
		}
	}
}
