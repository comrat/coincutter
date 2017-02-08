#include "circlerecognizer.h"
#include <QColor>
#include <iostream>
#include <numeric>
#include "convolution.h"


Circles CircleRecognizer::FindCircles(const QImage& image)
{
	Circles res;
	Binarize(image);
	return res;
}



QImage CircleRecognizer::Grayscale(const QImage& image)
{
	QImage img = image;

	for (int i = 0; i < img.height(); ++i) {
		uchar* scan = img.scanLine(i);
		int depth = 4;
		for (int j = 0; j < img.width(); ++j) {
			QRgb* rgbpixel = reinterpret_cast<QRgb*>(scan + j * depth);
			int gray = qGray(*rgbpixel);
			*rgbpixel = QColor(gray, gray, gray).rgba();
		}
	}

    return img;
}


QImage CircleRecognizer::Binarize(const QImage& image)
{
	QImage img = image;
	unsigned long sum = img.height() * img.width();
	HistVector hist(256, 0);

	for (int i = 0; i < img.height(); ++i) {
		uchar* scan = img.scanLine(i);
		int depth = 4;
		for (int j = 0; j < img.width(); ++j) {
			QRgb* rgbpixel = reinterpret_cast<QRgb*>(scan + j * depth);
			int gray = qGray(*rgbpixel);
			if (gray >= 0 && gray < 256)
				++hist.at(gray);
		}
	}

	double mu = 0;
	for (int t = 0; t < HistSize; ++t)
		mu += hist[t] * t;
	mu /= sum;

	double maxDisp = 0.0;
	int maxIdx = 0;

	for (HistVector::iterator t = hist.begin(); t != hist.end(); ++t) {
		double muLeft;
		double wLeft;
		double wRight;
		for (HistVector::iterator it = hist.begin(); it != t; ++it) {
			wLeft += *it;
			muLeft += *it * (it - hist.begin());
		}
		wLeft /= sum;
		wRight = 1 - wLeft;

		//FIXME
		if (wLeft < 0.0000005)
			continue;

		muLeft /= sum * wLeft;

		double muRight = (mu - muLeft * wLeft) / wRight;
		double disp = wLeft * wRight * (muLeft - muRight) * (muLeft - muRight);

		if (disp > maxDisp) {
			maxDisp = disp;
			maxIdx = t - hist.begin();
		}
	}

	//std::cout << "Otsu threshold: " << maxIdx << std::endl;

	for (int i = 0; i < img.height(); ++i) {
		uchar* scan = img.scanLine(i);
		int depth = 4;
		for (int j = 0; j < img.width(); ++j) {
			QRgb* rgbpixel = reinterpret_cast<QRgb*>(scan + j * depth);
			int gray = qGray(*rgbpixel);
			int val = gray > maxIdx ? 255 : 0;
			*rgbpixel = QColor(val, val, val).rgba();
		}
	}

    return img;
}
