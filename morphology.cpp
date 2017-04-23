#include "morphology.h"

namespace morphology
{

QImage Dilation(const QImage& image)
{
	QImage img(image.width(), image.height(), QImage::Format_RGB32);

	for (int i = 0; i < image.height(); ++i) {
		for (int j = 0; j < image.width(); ++j) {
			double val = qGray(image.pixel(j, i));
			if (val == 255) {
				if (j > 0)
					img.setPixel(j - 1, i, QColor(255, 255, 255).rgba());
				if (j < image.width() - 1)
					img.setPixel(j + 1, i, QColor(255, 255, 255).rgba());
				if (i > 0)
					img.setPixel(j, i - 1, QColor(255, 255, 255).rgba());
				if (i < image.width() - 1)
					img.setPixel(j, i + 1, QColor(255, 255, 255).rgba());
				img.setPixel(j, i, QColor(255, 255, 255).rgba());
			} else {
				img.setPixel(j, i, QColor(0, 0, 0).rgba());
			}
		}
	}

	return img;
}

}
