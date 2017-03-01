#ifndef MORPHOLOGY_H
#define MORPHOLOGY_H

#include <QImage>


class Morphology
{
public:
	static QImage Dilation(const QImage& image);
};

#endif // MORPHOLOGY_H
