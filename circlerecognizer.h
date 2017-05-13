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
	bool IsInternalCircle(const Circle& circle, const Circles& circles);
	bool IsSimilar(const Circle& circle, const Circles& circles);
	Circles RemoveExtraCircles(const Circles& circles);
};

#endif // CIRCLERECOGNIZER_H
