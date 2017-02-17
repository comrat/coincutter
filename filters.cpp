#include "filters.h"
#include <cmath>
#include <QColor>


QImage Filters::Sobel(const QImage& image)
{
	Convolution::Array kernel(3, Convolution::ArrayRow(3));
	kernel[0][0] = -1;
	kernel[0][1] = -2;
	kernel[0][2] = -1;

	kernel[1][0] = 0;
	kernel[1][1] = 0;
	kernel[1][2] = 0;

	kernel[2][0] = 1;
	kernel[2][1] = 2;
	kernel[2][2] = 1;
	Convolution conv(kernel);
	QImage Gy = conv.CalcGray(image);

	kernel[0][0] = -1;
	kernel[0][1] = 0;
	kernel[0][2] = 1;

	kernel[1][0] = -2;
	kernel[1][1] = 0;
	kernel[1][2] = 2;

	kernel[2][0] = -1;
	kernel[2][1] = 0;
	kernel[2][2] = 1;

	conv.SetKernel(kernel);
	QImage Gx = conv.CalcGray(image);

    QImage img(image.width(), image.height(), QImage::Format_RGB32);

	for (int i = 0; i < image.height(); ++i) {
		for (int j = 0; j < image.width(); ++j) {
			double gx = qGray(Gx.pixel(j, i));
			double gy = qGray(Gy.pixel(j, i));
			int val = sqrt(gx * gx + gy * gy);
			val = val < 0 ? 0 : (val >= 256 ? 255 : val);
			img.setPixel(j, i, QColor(val, val, val).rgba());
		}
	}

	return img;
}


QImage CannyThreshold(const QImage& image, int low, int high)
{
	if (low > 255)
		low = 255;
	if (high > 255)
		high = 255;

	int w = image.width();
	int h = image.height();
	QImage edge(w, h, QImage::Format_RGB32);

	for (int i = 0; i < h; ++i) {
		for (int j = 0; j < w; ++j) {
			edge.setPixel(i, j, image.pixel(i, j));
			if (edge.pixel(i, j) > high) {
				edge.setPixel(i, j, QColor(255, 255, 255).rgba());
			} else if(edge.pixel(i, j) < low) {
				edge.setPixel(i, j, QColor(0, 0, 0).rgba());
			} else {
				bool anyHigh = false;
				bool anyBetween = false;
				for (int x = i - 1; x < i + 2; ++x) {
					for (int y = j - 1; y < j + 2; ++y) {
						if (x <= 0 || y <= 0 || h || y > w) {
							continue;
						} else {
							if (edge.pixel(x,y) > high) {
								//TODO: add function for val setting
								edge.setPixel(i, j, QColor(255, 255, 255).rgba());
								anyHigh = true;
								break;
							} else if (edge.pixel(x, y) <= high && edge.pixel(x, y) >= low) {
								anyBetween = true;
							}
						}
					}
					if (anyHigh)
						break;
				}
				if (!anyHigh && anyBetween)
					for (int x = i - 2; x < i + 3; ++x) {
						for (int y = j - 1; y < j + 3; ++y) {
							if (x < 0 || y < 0 || x > h || y > w) {
								continue;
							} else {
								if (edge.pixel(x, y) > high) {
									edge.setPixel(i, j, QColor(255, 255, 255).rgba());
									anyHigh = true;
									break;
								}
							}
						}
						if (anyHigh)
							break;
					}

				if (!anyHigh)
					edge.setPixel(i, j, QColor(0, 0, 0).rgba());
			}
		}
	}
	return edge;
}


QImage Filters::CannyNonMax(const QImage& image, const Convolution::Array& angles)
{
	int w = image.width();
	int h = image.height();

	QImage nonMaxSupped(w - 2, h - 2, QImage::Format_RGB32);
	for (int i = 1; i < h - 1; ++i) {
		for (int j = 1; j < w - 1; ++j) {
			float angle = angles[i][j];
			nonMaxSupped.setPixel(i - 1, j - 1, image.pixel(i, j));

			//Horizontal Edge
			if (((-22.5 < angle) && (angle <= 22.5)) || ((157.5 < angle) && (angle <= -157.5)))
				if ((image.pixel(i, j) < image.pixel(i, j + 1)) || (image.pixel(i, j) < image.pixel(i, j - 1)))
					nonMaxSupped.setPixel(i - 1, j - 1,  QColor(0, 0, 0).rgba());

			//Vertical Edge
			if (((-112.5 < angle) && (angle <= -67.5)) || ((67.5 < angle) && (angle <= 112.5)))
				if ((image.pixel(i, j) < image.pixel(i + 1, j)) || (image.pixel(i, j) < image.pixel(i - 1, j)))
					nonMaxSupped.setPixel(i - 1, j - 1,  QColor(0, 0, 0).rgba());

			//-45 Degree Edge
			if (((-67.5 < angle) && (angle <= -22.5)) || ((112.5 < angle) && (angle <= 157.5)))
				if ((image.pixel(i, j) < image.pixel(i - 1, j + 1)) || (image.pixel(i, j) < image.pixel(i + 1, j - 1)))
					nonMaxSupped.setPixel(i - 1, j - 1,  QColor(0, 0, 0).rgba());

			//45 Degree Edge
			if (((-157.5 < angle) && (angle <= -112.5)) || ((22.5 < angle) && (angle <= 67.5)))
				if ((image.pixel(i, j) < image.pixel(i + 1, j + 1)) || (image.pixel(i, j) < image.pixel(i - 1, j - 1)))
					nonMaxSupped.setPixel(i - 1, j - 1,  QColor(0, 0, 0).rgba());
		}
	}
	return nonMaxSupped;
}


QImage Filters::Canny(const QImage& image)
{
	int w = image.width();
	int h = image.height();
	Convolution::Array angles;
	angles.resize(h);

	// Sobel
	Convolution::Array kernel(3, Convolution::ArrayRow(3));
	kernel[0][0] = -1;
	kernel[0][1] = -2;
	kernel[0][2] = -1;

	kernel[1][0] = 0;
	kernel[1][1] = 0;
	kernel[1][2] = 0;

	kernel[2][0] = 1;
	kernel[2][1] = 2;
	kernel[2][2] = 1;
	Convolution conv(kernel);
	QImage Gy = conv.CalcGray(image);

	kernel[0][0] = -1;
	kernel[0][1] = 0;
	kernel[0][2] = 1;

	kernel[1][0] = -2;
	kernel[1][1] = 0;
	kernel[1][2] = 2;

	kernel[2][0] = -1;
	kernel[2][1] = 0;
	kernel[2][2] = 1;

	conv.SetKernel(kernel);
	QImage Gx = conv.CalcGray(image);

	QImage img(w, h, QImage::Format_RGB32);
	for (int i = 0; i < h; ++i) {
		angles[i].resize(w, 0);
		for (int j = 0; j < w; ++j) {
			double gx = qGray(Gx.pixel(j, i));
			double gy = qGray(Gy.pixel(j, i));
			angles[i][j] = atan2(gy, gx);
			int val = sqrt(gx * gx + gy * gy);
			val = val < 0 ? 0 : (val >= 256 ? 255 : val);
			img.setPixel(j, i, QColor(val, val, val).rgba());
		}
	}

	QImage nonMaxSupped = CannyNonMax(img, angles);

	return image;
}


QImage Filters::Gauss(const QImage& image)
{
	Convolution::Array kernel(5, Convolution::ArrayRow(5));
	kernel[0][0] = 2;
	kernel[0][1] = 4;
	kernel[0][2] = 5;
	kernel[0][3] = 4;
	kernel[0][4] = 2;

	kernel[1][0] = 4;
	kernel[1][1] = 9;
	kernel[1][2] = 12;
	kernel[1][3] = 9;
	kernel[1][4] = 4;

	kernel[2][0] = 5;
	kernel[2][1] = 12;
	kernel[2][2] = 15;
	kernel[2][3] = 12;
	kernel[2][4] = 5;

	kernel[3][0] = 4;
	kernel[3][1] = 9;
	kernel[3][2] = 12;
	kernel[3][3] = 9;
	kernel[3][4] = 4;

	kernel[4][0] = 2;
	kernel[4][1] = 4;
	kernel[4][2] = 5;
	kernel[4][3] = 4;
	kernel[4][4] = 2;

	Convolution conv(kernel, 159);
	QImage img = conv.Calc(image);
	return img;
}
