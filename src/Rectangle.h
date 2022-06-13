#pragma once
#include "Shape.h"

class Rectangle : public Shape
{
private:
	double width, height;
public:
	Rectangle(double x, double y, double width, double height, const String& appearance);
	double getArea() const override;
	double getPerimeter() const override;
	bool includesPoint(double x, double y) const override;
	Shape* clone() const override;

	void print() const override;
	void translate(double y, double x) override;

	const double getWidth() const;
	const double getHeight() const;

	bool isWithinRectangle(const double& x, const double& y, const double& width, const double& height) const override;
	bool isWithinCircle(const double& x, const double& y, const double& radius) const override;

	void writeSVGline(std::ofstream& out) const override;
	void erasedMessage() const override;
};