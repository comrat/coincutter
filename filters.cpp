#include "filters.h"
#include "convolution.h"


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
	QImage img = conv.Calc(image);
	return img;
}


QImage Filters::Gauss(const QImage& image)
{
	Convolution::Array kernel(3, Convolution::ArrayRow(3));
	kernel[0][0] = 1;
	kernel[0][1] = 1;
	kernel[0][2] = 1;

	kernel[1][0] = 1;
	kernel[1][1] = 1;
	kernel[1][2] = 1;

	kernel[2][0] = 1;
	kernel[2][1] = 1;
	kernel[2][2] = 1;
	Convolution conv(kernel, 9);
	QImage img = conv.Calc(image);
	return img;
}
