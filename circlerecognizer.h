#ifndef CIRCLERECOGNIZER_H
#define CIRCLERECOGNIZER_H

#include <QImage>
#include <vector>
#include "Circle.h"


class CircleRecognizer
{
	QImage _img;

public:
	CircleRecognizer(const QImage& image);
	Circles FindCircles();

private:
	bool CheckCircle(const Circle& circle);
	bool CheckPixel(int x, int y);
};

#endif // CIRCLERECOGNIZER_H
