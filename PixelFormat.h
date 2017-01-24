#ifndef PIXELFORMAT_H
#define PIXELFORMAT_H

typedef unsigned int	uint;
typedef unsigned char	uchar;

enum PixelType { Binary = 8, Grayscale = 16, RGB = 24, ARGB = 32 };

class PixelFormat {
private:
	uint	_width;
	uint	_height;
	uint	_stride;
	uint	_pixelSize;

public:
	PixelFormat(PixelType type);

	int GetWidth() { return _width; }
	int GetHeight() { return _height; }
	int GetStride() { return _stride; }
};

#endif // PIXELFORMAT_H
