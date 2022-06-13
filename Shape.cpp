#include "Shape.h"

void Shape::copyFrom(const Shape& other)
{
	color = other.color;
	count = other.count;
	points = new point[other.count];

	for (size_t i = 0; i < count; ++i)
		points[i] = other.points[i];
}

void Shape::free()
{
	delete[] points;
}

Shape::Shape(size_t count) : count(count)
{
	color = "";
	points = new point[count]; 
}

Shape::Shape(const Shape& other)
{
	copyFrom(other);
}

Shape& Shape::operator=(const Shape& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

Shape::~Shape()
{
	free();
}

const Shape::point& Shape::getPointByIndex(size_t index) const
{
	if (index >= count)
		throw "Invalid index!";

	return points[index];
}

void Shape::setPoint(size_t index, double x, double y)
{
	if (index >= count)
		throw "Invalid index!";

	points[index] = point(x, y);
}