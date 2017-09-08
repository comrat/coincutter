typedef unsigned char	uchar;
#include <QImage>

class GrayImage {
private:
	uchar*	_data;
	int		_width;
	int		_height;

public:
	GrayImage(const QImage& img);
	~GrayImage();

	int GetWidth() const { return _width; }
	int GetHeight() const { return _height; }

	uchar GetPixel(int x, int y) const
	{ return _data[y * _width + x]; }

	void SetPixel(int x, int y, uchar value)
	{ _data[y * _width + x] = value; }
};
