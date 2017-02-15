#include "filters.h"
#include "convolution.h"
#include <cmath>
#include <QColor>


QImage Filters::Sobel(const QImage& image)
{
	Convolution::Array kernel(3, Convolution::ArrayRow(3));
	kernel[0][0] = -1;
	kernel[0][1] = -2;
	kernel[0][2] = -1;

	kernel[1][0] = 0;
	kernel[1][1] = 0;
	kernel[1][2] = 0;

	kernel[2][0] = 1;
	kernel[2][1] = 2;
	kernel[2][2] = 1;
	Convolution conv(kernel);
	QImage Gy = conv.CalcGray(image);

	kernel[0][0] = -1;
	kernel[0][1] = 0;
	kernel[0][2] = 1;

	kernel[1][0] = -2;
	kernel[1][1] = 0;
	kernel[1][2] = 2;

	kernel[2][0] = -1;
	kernel[2][1] = 0;
	kernel[2][2] = 1;
	//TODO: impl method for kernel setting
	Convolution conv2(kernel);
	QImage Gx = conv2.CalcGray(image);

    QImage img(image.width(), image.height(), QImage::Format_RGB32);

	for (int i = 0; i < image.height(); ++i) {
		for (int j = 0; j < image.width(); ++j) {
			double gx = qGray(Gx.pixel(j, i));
			double gy = qGray(Gy.pixel(j, i));
			int val = sqrt(gx * gx + gy * gy);
			val = val < 0 ? 0 : (val >= 256 ? 255 : val);
			img.setPixel(j, i, QColor(val, val, val).rgba());
		}
	}

	return Gx;
}


QImage Filters::Canny(const QImage& image)
{
	Convolution::Array kernel(3, Convolution::ArrayRow(3));
	kernel[0][0] = -2;
	kernel[0][1] = -1;
	kernel[0][2] = 0;

	kernel[1][0] = -1;
	kernel[1][1] = 1;
	kernel[1][2] = 1;

	kernel[2][0] = 0;
	kernel[2][1] = 1;
	kernel[2][2] = 2;
	Convolution conv(kernel);
	QImage img = conv.CalcGray(Gauss(image));
	return img;
}


QImage Filters::Gauss(const QImage& image)
{
	Convolution::Array kernel(5, Convolution::ArrayRow(5));
	kernel[0][0] = 2;
	kernel[0][1] = 4;
	kernel[0][2] = 5;
	kernel[0][3] = 4;
	kernel[0][4] = 2;

	kernel[1][0] = 4;
	kernel[1][1] = 9;
	kernel[1][2] = 12;
	kernel[1][3] = 9;
	kernel[1][4] = 4;

	kernel[2][0] = 5;
	kernel[2][1] = 12;
	kernel[2][2] = 15;
	kernel[2][3] = 12;
	kernel[2][4] = 5;

	kernel[3][0] = 4;
	kernel[3][1] = 9;
	kernel[3][2] = 12;
	kernel[3][3] = 9;
	kernel[3][4] = 4;

	kernel[4][0] = 2;
	kernel[4][1] = 4;
	kernel[4][2] = 5;
	kernel[4][3] = 4;
	kernel[4][4] = 2;

	Convolution conv(kernel, 159);
	QImage img = conv.Calc(image);
	return img;
}
