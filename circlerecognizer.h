#ifndef CIRCLERECOGNIZER_H
#define CIRCLERECOGNIZER_H

#include <QImage>
#include "Circle.h"

#include <vector>

const int HistSize = 256;


class CircleRecognizer
{
private:
	typedef std::vector<int>	HistVector;

public:
	Circles FindCircles(const QImage& image);

//private:
    QImage Binarize(const QImage& image);
};

#endif // CIRCLERECOGNIZER_H
