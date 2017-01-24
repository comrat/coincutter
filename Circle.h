#ifndef CIRCLE_H
#define CIRCLE_H

struct Circle {
	int x;
	int y;
	int radius;

	explicit Circle(int x = 0, int y = 0, int radius = 0) : x(x), y(y), radius(radius) { }
};

typedef std::vector<Circle>		Circles;

#endif // CIRCLE_H
