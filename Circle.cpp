#include "Circle.h"

#include <cmath>

bool operator== (const Circle& lhs, const Circle& rhs)
{ return lhs.x == rhs.x && lhs.y == rhs.y && lhs.radius == rhs.radius; }

bool operator!= (const Circle& lhs, const Circle& rhs)
{ return !(lhs == rhs); }


bool Circle::Contains(const Circle& other) const
{
	int otherX = other.x - x;
	int otherY = other.y - y;
	return otherX * otherX + otherY * otherY < radius * radius && radius > other.radius;
}


int Circle::CenterDistance(const Circle& other) const
{
	int deltaX = other.x - this->x;
	int deltaY = other.y - this->y;
	return sqrt(deltaX * deltaX + deltaY * deltaY);
}
