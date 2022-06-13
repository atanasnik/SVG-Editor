#pragma once
#include "String.h"
#include <cmath>
#include <fstream>
class Shape
{
protected:
	String color;
	struct point
	{
		point() :x(0.0), y(0.0) {}
		point(double x, double y) :x(x), y(y) {}
		double x;
		double y;
		double getDist(const point& other) const
		{
			double d_x = x - other.x;
			double d_y = y - other.y;

			return sqrt(d_x * d_x + d_y * d_y);
		}
	};
private:
	point* points;
	size_t count;

	void copyFrom(const Shape& other);
	void free();
public:
	const point& getPointByIndex(size_t index) const;

	Shape(size_t count);

	Shape(const Shape& other);
	Shape& operator=(const Shape& other);
	virtual ~Shape();

	void setPoint(size_t index, double x, double y);
	virtual double getArea() const = 0;
	virtual double getPerimeter()  const = 0;
	virtual bool includesPoint(double x, double y) const = 0;
	virtual Shape* clone() const = 0;

	virtual void print() const = 0;
	virtual void translate(double y, double x) = 0;

	virtual bool isWithinRectangle(const double& x, const double& y, const double& width, const double& height) const = 0;
	virtual bool isWithinCircle(const double& x, const double& y, const double& radius) const = 0;
	virtual void writeSVGline(std::ofstream& file) const = 0;
	virtual void erasedMessage() const = 0;
};