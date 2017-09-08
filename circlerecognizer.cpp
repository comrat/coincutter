#include "circlerecognizer.h"
#include "filters.h"
#include "morphology.h"

#include <QColor>

#include <iostream>
#include <cmath>


Circles CircleRecognizer::FindCircles()
{
	Circles res;
	int w = _img->GetWidth();
	int h = _img->GetHeight();
	int minR = (int)((w > h ? w : h) * 0.025);
	int maxR = (int)((w > h ? w : h) * 0.5);
	for (int r = minR; r < maxR; ++r) {
		int width = w - r - 1;
		int height = h - r - 1;
		for (int x = r; x < width; ++x) {
			for (int y = r; y < height; ++y) {
				//std::cout << "R: " << r << std::endl;
				Circle c(x, y, r);
				if (CircleRecognizer::CheckCircle(c))
					res.push_back(c);
			}
		}
	}
	res = RemoveExtraCircles(res);
	return res;
}


bool CircleRecognizer::IsSimilar(const Circle& circle, const Circles& circles)
{
	int w = _img->GetWidth();
	int h = _img->GetHeight();
	int delta = (int)((w > h ? w : h) * 0.025);
	for (Circles::const_iterator it = circles.begin(); it != circles.end(); ++it)
	{
		if (circle == *it)
			continue;
		int deltaRadius = circle.radius - it->radius;
		int radiusDist = sqrt(deltaRadius * deltaRadius);
		int centerDist = circle.CenterDistance(*it);
		if (radiusDist < delta && centerDist < delta)
			return true;
	}
	return false;
}


bool CircleRecognizer::IsInternalCircle(const Circle& circle, const Circles& circles)
{
	for (Circles::const_iterator it = circles.begin(); it != circles.end(); ++it)
		if (circle != *it && it->Contains(circle))
			return true;
	return false;
}


Circles CircleRecognizer::RemoveExtraCircles(const Circles& circles)
{
	Circles res;
	for (Circles::const_iterator it = circles.begin(); it != circles.end(); ++it)
		if (!IsInternalCircle(*it, circles) && !IsSimilar(*it, res))
			res.push_back(*it);
	return res;
}


CircleRecognizer::CircleRecognizer(const QImage& image)
{
	//_img = new GrayImage(image);
	QImage preproc = filters::Canny(image);
	preproc = morphology::Dilation(preproc);
	_img = new GrayImage(image);
}


bool CircleRecognizer::CheckPixel(int x, int y)
{ return (x < 0 || y < 0 || x >= _img->GetWidth() || y >= _img->GetHeight()) ? true : (qGray(_img->GetPixel(x, y)) == 255); }


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

	return total == 0 ? false : (match * 1.0 / total > 0.5);
}
