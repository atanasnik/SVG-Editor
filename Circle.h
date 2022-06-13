#pragma once
#include "Shape.h"

class Circle : public Shape
{
	double radius;
public:
	Circle(double x, double y, double radius, const String& appearance);

	double getArea() const override;
	double getPerimeter() const override;
	bool includesPoint(double x, double y) const override;
	Shape* clone() const override;

	void print() const override;
	void translate(double y, double x) override;

	const double getRadius() const;
	
	bool isWithinRectangle(const double& x, const double& y, const double& width, const double& height) const override;
	bool isWithinCircle(const double& x, const double& y, const double& radius) const override;

	void writeSVGline(std::ofstream& out) const override;
	void erasedMessage() const override;
};