#include "convolution.h"
#include <stdexcept>
#include <QColor>


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

			for (int k = -_shift; k <= _shift; ++k) {
				for (int l = -_shift; l <= _shift; ++l) {
					int x = j + k;
					if (x < 0 || x >= image.width())
						continue;
					int y = i + l;
					if (y < 0 || y >= image.height())
						continue;
					int val = _kernel[k + _shift][l + _shift];
					QRgb pix = image.pixel(x, y);
					red += val * qRed(pix);
					green += val * qGreen(pix);
					blue += val * qBlue(pix);
				}
			}
			red /= _divisor;
			red = red < 0 ? 0 : (red >= 256 ? 255 : red);

			green /= _divisor;
			green = green < 0 ? 0 : (green >= 256 ? 255 : green);

			blue /= _divisor;
			blue = blue < 0 ? 0 : (blue >= 256 ? 255 : blue);
			img.setPixel(j, i, QColor(red, green, blue).rgba());
		}
	}

    return img;
}
