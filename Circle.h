#ifndef CIRCLE_H
#define CIRCLE_H

#include <vector>

struct Circle {
	int x;
	int y;
	int radius;

	explicit Circle(int x = 0, int y = 0, int radius = 0) : x(x), y(y), radius(radius) { }

	bool Contains(const Circle& other) const;
	int CenterDistance(const Circle& other) const;

	friend bool operator== (const Circle& lhs, const Circle& rhs);
	friend bool operator!= (const Circle& lhs, const Circle& rhs);
};


typedef std::vector<Circle>		Circles;

#endif // CIRCLE_H
