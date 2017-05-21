#include "GrayImage.h"
#include <QColor>

GrayImage::GrayImage(const QImage& img)
{
	_width = img.width();
	_height = img.height();
	_data = new uchar[_width * _height];

	for (int x = 0; x < _width; ++x)
		for (int y = 0; y < _height; ++y)
			SetPixel(x, y, qGray(img.pixel(x, y)));
}

GrayImage::~GrayImage()
{ delete[] _data; }
