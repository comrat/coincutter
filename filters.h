#ifndef FILTERS_H
#define FILTERS_H

#include <QImage>
#include "convolution.h"


namespace filters
{
	typedef std::vector<int>	HistVector;
	const int HistSize = 256;

	QImage Sobel(const QImage& image);
	QImage Gauss(const QImage& image);
	QImage Canny(const QImage& image);
	QImage Grayscale(const QImage& image);
    QImage BinarizeOtsu(const QImage& image);

	QImage CannyNonMax(const QImage& image, const Convolution::Array& angles);
	QImage CannyThreshold(const QImage& image, int low, int high);
};

#endif // FILTERS_H
