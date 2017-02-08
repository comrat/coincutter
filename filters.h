#ifndef FILTERS_H
#define FILTERS_H

#include <QImage>


struct Filters
{
	static QImage Canny(const QImage& image);
	static QImage Gauss(const QImage& image);
};

#endif // FILTERS_H
