#include "Circle.h"

bool operator== (const Circle& lhs, const Circle& rhs)
{ return lhs.x == rhs.x && lhs.y == rhs.y && lhs.radius == rhs.radius; }

bool Circle::Contains(const Circle& other) const
{
	int otherX = other.x - x;
	int otherY = other.y - y;
	return otherX * otherX + otherY * otherY < radius * radius && radius > other.radius;
}
