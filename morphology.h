#ifndef MORPHOLOGY_H
#define MORPHOLOGY_H

#include <QImage>
#include "convolution.h"


namespace morphology
{
	QImage Dilation(const QImage& image);
};

#endif // MORPHOLOGY_H
