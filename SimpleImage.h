typedef unsigned char	uchar;
#include <QImage>

class SimpleImage {
private:
	uchar*	_data;
	int		_size;
	int		_width;
	int		_height;

public:
	SimpleImage(const QImage& img, int size);

	~SimpleImage();

	uchar GetPixel(int x, int y)
	{ return _data[y * _width * _size + y * _size]; }
};
