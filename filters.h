#ifndef FILTERS_H
#define FILTERS_H

#include <QImage>
#include "convolution.h"


struct Filters
{
private:
	typedef std::vector<int>	HistVector;
	static const int HistSize = 256;

public:
	static QImage Sobel(const QImage& image);
	static QImage Gauss(const QImage& image);
	static QImage Canny(const QImage& image);
	static QImage Grayscale(const QImage& image);
    static QImage BinarizeOtsu(const QImage& image);

private:
	static QImage CannyNonMax(const QImage& image, const Convolution::Array& angles);
	static QImage CannyThreshold(const QImage& image, int low, int high);
};

#endif // FILTERS_H
