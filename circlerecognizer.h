#ifndef CIRCLERECOGNIZER_H
#define CIRCLERECOGNIZER_H

#include <QImage>
#include "Circle.h"


class CircleRecognizer
{
public:
	static Circles FindCircles(const QImage& image);
};

#endif // CIRCLERECOGNIZER_H
