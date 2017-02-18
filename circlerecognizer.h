#ifndef CIRCLERECOGNIZER_H
#define CIRCLERECOGNIZER_H

#include <QImage>
#include <vector>
#include "Circle.h"


class CircleRecognizer
{
public:
	Circles FindCircles(const QImage& image);

private:
	bool CheckCircle(const QImage& image, const Circle& circle);
	bool CheckPixel(const QImage& image, int x, int y);
};

#endif // CIRCLERECOGNIZER_H
