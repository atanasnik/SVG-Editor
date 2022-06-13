#pragma once
#include "Shape.h"

class Line : public Shape
{
private:
	double length;
public:
	Line(double x1, double y1, double x2, double x3, const String& appearance);
	double getArea() const override;
	double getPerimeter() const override;
	bool includesPoint(double x, double y) const override;
	Shape* clone() const override;

	void print() const override;
	void translate(double y, double x) override;
	
	bool isWithinRectangle(const double& x, const double& y, const double& width, const double& height) const override;
	bool isWithinCircle(const double& x, const double& y, const double& radius) const override;

	void writeSVGline(std::ofstream& out) const override;
	void erasedMessage() const override;
};

double min(double a, double b);
double max(double a, double b);