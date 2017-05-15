#include "SimpleImage.h"

SimpleImage::SimpleImage(const QImage& img, int size = 3)
{
	_width = img.width();
	_height = img.height();
	_size = size;
	_data = new uchar[_width * _height * _size];
}

SimpleImage::~SimpleImage()
{ delete[] _data; }
