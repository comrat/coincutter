#ifndef FILTERS_H
#define FILTERS_H

#include <QImage>
#include "convolution.h"


struct Filters
{
public:
	static QImage Sobel(const QImage& image);
	static QImage Gauss(const QImage& image);
	static QImage Canny(const QImage& image);

private:
	static QImage CannyNonMax(const QImage& image, const Convolution::Array& angles);
	static QImage CannyThreshold(const QImage& image, int low, int high);
};

#endif // FILTERS_H
