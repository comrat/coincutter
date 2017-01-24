#include "PixelFormat.h"


PixelFormat::PixelFormat(PixelType type)
{
	const int bitsPerByte = 8;
	_pixelSize = type / bitsPerByte;
}
