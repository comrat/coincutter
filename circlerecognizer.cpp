#include "circlerecognizer.h"
#include <QColor>

#include <iostream>

Circles CircleRecognizer::FindCircles(const QImage& image)
{
	Circles res;
	Binarize(image);
	return res;
}

QImage CircleRecognizer::Binarize(const QImage& image)
{
	QImage img = image;
	for (int i = 0; i < img.height(); ++i) {
		uchar* scan = img.scanLine(i);
		int depth = 4;
		for (int j = 0; j < img.width(); ++j) {
			QRgb* rgbpixel = reinterpret_cast<QRgb*>(scan + j * depth);
			int val = qGray(*rgbpixel) > 128 ? 255 : 0;
			*rgbpixel = QColor(val, val, val).rgba();
		}
	}
    return img;
}
