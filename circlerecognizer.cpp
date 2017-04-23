#include "circlerecognizer.h"
#include "filters.h"

#include <QColor>

#include <iostream>


Circles CircleRecognizer::FindCircles(const QImage& image)
{
	Circles res;
	QImage filtered = filters::Canny(image);
	int w = filtered.width();
	int h = filtered.height();
	int minR = (int)((w > h ? w : h) * 0.025);
	int maxR = (int)((w > h ? w : h) * 0.5);
	for (int r = minR; r < maxR; ++r) {
		int width = w - r - 1;
		int height = h - r - 1;
		//std::cout << "R: " << r << "; min: " << minR << ", maxR: " << maxR << std::endl;
		for (int x = r; x < width; ++x) {
			for (int y = r; y < height; ++y) {
				Circle c(x, y, r);
				if (CircleRecognizer::CheckCircle(filtered, c))
					res.push_back(c);
					//std::cout << "FOUND CIRCLE: x: " << x << ", y: " << y << ", r: " << r << std::endl;
			}
		}
	}
	return res;
}


bool CircleRecognizer::CheckPixel(const QImage& image, int x, int y)
{ return (x < 0 || y < 0 || x >= image.width() || y >= image.height()) ? true : (qGray(image.pixel(x, y)) == 255); }


bool CircleRecognizer::CheckCircle(const QImage& image, const Circle& circle)
{
	int x0 = circle.x;
	int y0 = circle.y;
	int x = circle.radius;
	int y = 0;
	int err = 0;
	int total = 0;
	int match = 0;

	while (x >= y) {
		match += CircleRecognizer::CheckPixel(image, x0 + x, y0 + y) ? 1 : 0;
		match += CircleRecognizer::CheckPixel(image, x0 + y, y0 + x) ? 1 : 0;
		match += CircleRecognizer::CheckPixel(image, x0 - y, y0 + x) ? 1 : 0;
		match += CircleRecognizer::CheckPixel(image, x0 - x, y0 + y) ? 1 : 0;
		match += CircleRecognizer::CheckPixel(image, x0 - x, y0 - y) ? 1 : 0;
		match += CircleRecognizer::CheckPixel(image, x0 - y, y0 - x) ? 1 : 0;
		match += CircleRecognizer::CheckPixel(image, x0 + y, y0 - x) ? 1 : 0;
		match += CircleRecognizer::CheckPixel(image, x0 + x, y0 - y) ? 1 : 0;
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

	//std::cout << "Total: " << total << "; match: " << match << std::endl;
	return total == 0 ? false : (match * 1.0 / total > 0.7);
}
