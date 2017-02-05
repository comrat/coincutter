#include "convolution.h"
#include <stdexcept>
#include <QColor>

#include <iostream>


QImage Convolution::Calc(const QImage& image)
{
	if (!_divisor)
		throw std::overflow_error("Divide by zero exception");

    QImage img(image.width(), image.height(), QImage::Format_RGB32);

	for (int i = 0; i < image.height(); ++i) {
		for (int j = 0; j < image.width(); ++j) {
			int red = 0;
			int green = 0;
			int blue = 0;

			for (int k = -_shift; k < _shift; ++k) {
				for (int l = -_shift; l < _shift; ++l) {
					int x = j + k;
					if (x < 0)
						continue;
					int y = i + l;
					if (y < 0)
						continue;
					int val = _kernel[k + _shift][l + _shift];
					QRgb pix = image.pixel(x, y);
					red += val * qRed(pix);
					green += val * qGreen(pix);
					blue += val * qBlue(pix);
				}
			}
			img.setPixel(j, i, QColor(red / _divisor, green / _divisor, blue / _divisor).rgba());
		}
	}

    return img;
}
