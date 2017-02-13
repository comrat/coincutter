#ifndef FILTERS_H
#define FILTERS_H

#include <QImage>


struct Filters
{
	static QImage Sobel(const QImage& image);
	static QImage Gauss(const QImage& image);
	static QImage Canny(const QImage& image);
};

#endif // FILTERS_H
