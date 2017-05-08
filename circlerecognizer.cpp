#include "circlerecognizer.h"
#include "filters.h"
#include "morphology.h"

#include <QColor>

#include <iostream>


Circles CircleRecognizer::FindCircles()
{
	Circles res;
	int w = _img.width();
	int h = _img.height();
	int minR = (int)((w > h ? w : h) * 0.025);
	int maxR = (int)((w > h ? w : h) * 0.5);
	for (int r = minR; r < maxR; ++r) {
		int width = w - r - 1;
		int height = h - r - 1;
		for (int x = r; x < width; ++x) {
			for (int y = r; y < height; ++y) {
				Circle c(x, y, r);
				if (CircleRecognizer::CheckCircle(c))
					res.push_back(c);
			}
		}
	}
	return res;
}


CircleRecognizer::CircleRecognizer(const QImage& image) : _img(image)
{
	_img = filters::Canny(_img);
	_img = morphology::Dilation(_img);
}


bool CircleRecognizer::CheckPixel(int x, int y)
{ return (x < 0 || y < 0 || x >= _img.width() || y >= _img.height()) ? true : (qGray(_img.pixel(x, y)) == 255); }


bool CircleRecognizer::CheckCircle(const Circle& circle)
{
	int x0 = circle.x;
	int y0 = circle.y;
	int x = circle.radius;
	int y = 0;
	int err = 0;
	int total = 0;
	int match = 0;

	while (x >= y) {
		match += CircleRecognizer::CheckPixel(x0 + x, y0 + y) ? 1 : 0;
		match += CircleRecognizer::CheckPixel(x0 + y, y0 + x) ? 1 : 0;
		match += CircleRecognizer::CheckPixel(x0 - y, y0 + x) ? 1 : 0;
		match += CircleRecognizer::CheckPixel(x0 - x, y0 + y) ? 1 : 0;
		match += CircleRecognizer::CheckPixel(x0 - x, y0 - y) ? 1 : 0;
		match += CircleRecognizer::CheckPixel(x0 - y, y0 - x) ? 1 : 0;
		match += CircleRecognizer::CheckPixel(x0 + y, y0 - x) ? 1 : 0;
		match += CircleRecognizer::CheckPixel(x0 + x, y0 - y) ? 1 : 0;
		total += 8;

		if (err <= 0) {
			y += 1;
			err += 2 * y + 1;
		}
		if (err > 0) {
			x -= 1;
			err -= 2 * x + 1;
		}
	}

	return total == 0 ? false : (match * 1.0 / total > 0.7);
}
