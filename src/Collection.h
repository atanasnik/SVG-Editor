#pragma once
#include <fstream>
#include "Shape.h"
#include "Circle.h"
#include "Line.h"
#include "Rectangle.h"

class Collection
{
private:
	Shape** arr;
	size_t count;
	size_t capacity;

	void copyFrom(const Collection& other);
	void free();
	void resize(size_t newCapacity);
	void reset();
public:
	Collection();
	Collection(const Collection& other);
	Collection& operator=(const Collection& other);
	~Collection();

	void addShape(const Shape& other);
	void toErase(const String& input);
	void removeShape(size_t index);

	void printAll() const;
	void allAreas() const;
	void allPerimeters() const;
	double getPerimeterByIndex(size_t ind) const;
	double getAreaByIndex(size_t ind) const;
	double getincludesPointByIndex(size_t ind, int x, int y) const;
	
	void takeTranslateInput(const String& input);
	void translation(double y, double x, int index = -1);
	void create(const String&);

	void printWithin(const String& input) const;

	int parseRectangle(String&, double&, double&, double&, double&, size_t&) const;
	int parseCircle(String& temp, double& x, double& y, double& radius, size_t& numberLen) const;
	int parseLine(String& temp, double& x1, double& y1, double& x2, double& y2, size_t& numberLen) const;
	void parsePoint(String& temp, double& x, double& y, size_t numberLen);
	void pointIn(const String& input);

	void validationMessage(const String& shape) const;

	void playFile(const String& input, String&, String&, bool&);
	void loadFile(std::fstream& file, String& copyFile);
	void parseSVGline(char buff[], bool& validClosing);
	void writeToFile(const String& name, String& copyFile);


	void Menu();
	void instructions();
};