#ifndef CONVOLUTION_H
#define CONVOLUTION_H

#include <QImage>
#include <vector>


class Convolution
{
public:
	typedef std::vector<int>			ArrayRow;
	typedef std::vector< ArrayRow >		Array;

private:
	int		_size;
	int		_shift;
	int		_divisor;
	Array	_kernel;

public:
    Convolution(int size = 3, int divisor = 1) : _size(size), _shift(size / 2), _divisor(divisor)
	{
		_kernel.resize(_size);
		for (int i = 0; i < _size; ++i)
			_kernel[i].resize(_size, 0);
	}

    Convolution(const Array& arr, int divisor = 1) : _size(arr.size()), _shift(_size / 2), _divisor(divisor), _kernel(arr) { }

	QImage Calc(const QImage& image);
	QImage CalcGray(const QImage& image);
};

#endif // CONVOLUTION_H
