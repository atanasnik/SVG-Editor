#include "Circle.h"
#include <iostream>
#include "Rectangle.h"

const double PI = 3.1415;
Circle::Circle(double x, double y, double radius, const String& appearance) : Shape(1), radius(radius)
{
	setPoint(0, x, y);
	color = appearance;
}

double Circle::getArea() const
{
	return PI * radius * radius;
}

double Circle::getPerimeter() const
{
	return 2 * PI * radius;
}

bool Circle::includesPoint(double x, double y) const
{
	point p(x, y);
	return p.getDist(getPointByIndex(0)) <= radius;
}

Shape* Circle::clone() const
{
	return new Circle(*this);
}
void Circle::print() const
{
	std::cout << "circle "
		<< getPointByIndex(0).x << " "
		<< getPointByIndex(0).y << " "
		<< radius << " "
		<< color << std::endl;
}

void Circle::translate(double y, double x)
{
	setPoint(0, getPointByIndex(0).x + x, getPointByIndex(0).y + y);
}

bool Circle::isWithinRectangle(const double& x, const double& y, const double& width, const double& height) const
{
	Rectangle temp(x, y, width, height, color);

	point p0(temp.getPointByIndex(0).x, getPointByIndex(0).y); 
	point p1(getPointByIndex(0).x, temp.getPointByIndex(1).y);
	point p2(temp.getPointByIndex(2).x, getPointByIndex(0).y); 
	point p3(getPointByIndex(0).x, temp.getPointByIndex(3).y);

	return
		temp.includesPoint(getPointByIndex(0).x, getPointByIndex(0).y)
		&&
		getPointByIndex(0).getDist(p0) >= radius // distance from the center of the circle to the left side of the rectangle
		&&
		getPointByIndex(0).getDist(p1) >= radius // distance to the upper side
		&&
		getPointByIndex(0).getDist(p2) >= radius // distance to the right side
		&&
		getPointByIndex(0).getDist(p3) >= radius; // distance to the lower side
}

bool Circle::isWithinCircle(const double& x, const double& y, const double& radius) const
{
	Circle temp(x, y, radius, color);

	if (temp.getPointByIndex(0).x == getPointByIndex(0).x && temp.getPointByIndex(0).y == getPointByIndex(0).y)
		return radius >= this->radius;

	return temp.getPointByIndex(0).getDist(getPointByIndex(0)) <= radius - this->radius;
}

void Circle::writeSVGline(std::ofstream& out) const
{
	String toSave = " <circle cx=\"";
	out << toSave;
	out << getPointByIndex(0).x;
	toSave = "\" cy=\"";
	out << toSave;
	out << getPointByIndex(0).y;
	toSave = "\" r=\"";
	out << toSave;
	out << radius;
	toSave = "\" fill=\"";
	toSave += color;
	toSave += "\" />";

	out << toSave;
	out << '\n';
}

void Circle::erasedMessage() const
{
	std::cout << "Erased a circle";
}

const double Circle::getRadius() const
{
	return radius;
}

