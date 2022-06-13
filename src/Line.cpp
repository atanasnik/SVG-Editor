#include "Line.h"
#include <iostream>
#include "Circle.h"
#include "Rectangle.h"
Line::Line(double x1, double y1, double x2, double y2, const String& appearance) : Shape(2)
{
	setPoint(0, x1, y1);
	setPoint(1, x2, y2);
	length = getPointByIndex(0).getDist(getPointByIndex(1));
	color = appearance;
}

double Line::getArea() const
{
	return 0.0;
}

double Line::getPerimeter() const
{
	return length;
}

bool Line::includesPoint(double x, double y) const
{
	point p(x, y);
	//using the x and y coordinates of the point in the line's general equation and checking if it is equal to 0
	// (y1 - y0) * x - (x1 - x0) * y - (y1 - y0) * x0  + (x1 - x0) * y0 = 0
	return (getPointByIndex(1).y - getPointByIndex(0).y) * p.x
		 - (getPointByIndex(1).x - getPointByIndex(0).x) * p.y
		 - (getPointByIndex(1).y - getPointByIndex(0).y) * getPointByIndex(0).x
		 + (getPointByIndex(1).x - getPointByIndex(0).x) * getPointByIndex(0).y == 0
		&&
		p.x >= min(getPointByIndex(1).x, getPointByIndex(0).x)
		&&
		p.x <= max(getPointByIndex(1).x, getPointByIndex(0).x)
		&&
		p.y >= min(getPointByIndex(1).y, getPointByIndex(0).y)
		&&
		p.y <= max(getPointByIndex(1).y, getPointByIndex(0).y);
	
}

Shape* Line::clone() const
{
	return new Line(*this);
}

void Line::print() const
{
	std::cout << "line "
		<< getPointByIndex(0).x << " "
		<< getPointByIndex(0).y << " "
		<< getPointByIndex(1).x << " "
		<< getPointByIndex(1).y << " "
		<< color << std::endl;
}

void Line::translate(double y, double x)
{
	for (size_t i = 0; i < 2; ++i)
		setPoint(i, getPointByIndex(i).x + x, getPointByIndex(i).y + y);
}

bool Line::isWithinRectangle(const double& x, const double& y, const double& width, const double& height) const
{
	Rectangle temp(x, y, width, height, "");
	return	temp.includesPoint(getPointByIndex(0).x, getPointByIndex(0).y)
			&&
			temp.includesPoint(getPointByIndex(1).x, getPointByIndex(1).y);
}

bool Line::isWithinCircle(const double& x, const double& y, const double& radius) const
{
	Circle temp(x, y, radius, "");

	return	temp.includesPoint(getPointByIndex(0).x, getPointByIndex(0).y)
			&&
			temp.includesPoint(getPointByIndex(1).x, getPointByIndex(1).y)
			&&
			length <= temp.getRadius() * 2;
}

void Line::writeSVGline(std::ofstream& out) const
{
	String toSave = " <line x1=\"";
	out << toSave;
	out << getPointByIndex(0).x;
	toSave = "\" y1=\"";
	out << toSave;
	out << getPointByIndex(0).y;
	toSave = "\" x2=\"";
	out << toSave;
	out << getPointByIndex(1).x;
	toSave = "\" y2=\"";
	out << toSave;
	out << getPointByIndex(1).y;
	toSave = "\" fill=\"";
	toSave += color;
	toSave += "\" />";

	out << toSave;
	out << '\n';
}

void Line::erasedMessage() const
{
	std::cout << "Successfully erased line";
}

double min(double a, double b)
{
	return (a < b ? a : b);
}

double max(double a, double b)
{
	return (a > b ? a : b);
}
