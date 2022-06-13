#include "Collection.h"
#include <iostream>
void Collection::copyFrom(const Collection& other)
{
	arr = new Shape * [other.count];
	count = other.count;
	capacity = other.capacity;

	for (size_t i = 0; i < count; i++)
		arr[i] = other.arr[i]->clone();
}

void Collection::free()
{
	for (size_t i = 0; i < count; ++i)
		delete arr[i];
	delete[] arr;
}

void Collection::resize(size_t newCapacity)
{
	capacity = newCapacity;
	Shape** temp = new Shape * [capacity];
	for (size_t i = 0; i < count; ++i)
		temp[i] = arr[i];
	delete[] arr;
	arr = temp;
	temp = nullptr;
}

void Collection::reset()
{
	free();
	capacity = 8;
	count = 0;
	arr = new Shape * [capacity];
}

Collection::Collection() : capacity(8), count(0)
{
	arr = new Shape * [capacity];
}

Collection::Collection(const Collection& other)
{
	copyFrom(other);
}

Collection& Collection::operator=(const Collection& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

Collection::~Collection()
{
	free();
}

void Collection::addShape(const Shape& other)
{
	if (count >= capacity)
		resize(capacity * 2);
	arr[count++] = other.clone();
}

void Collection::toErase(const String& input)
{
	String temp(input);
	temp.reverse();
	temp.shorten(temp.getSize() - strlen("erase "));
	temp.reverse();
	double index;
	size_t countLen;
	temp.extractDouble(index, countLen);
	if (index <= 0)
	{
		std::cout << "Invalid index!" << std::endl;
		return;
	}
	if (index > count)
	{
		std::cout << "There is no figure with index " << index << "!" << std::endl;
		return;
	}
	arr[size_t(index) - 1]->erasedMessage();
	std::cout << "(" << size_t(index) << ")" << std::endl;
	removeShape(size_t(index) - 1);
}

void Collection::removeShape(size_t index)
{
	if (index >= count)
		throw "Out of range!";
	delete arr[index];
	for (size_t i = index; i < count - 1; ++i)
		arr[i] = arr[i + 1];
	--count;
	resize(count);
}

void Collection::printAll() const
{
	if (count == 0)
		std::cout << "There are no shapes yet..." << std::endl;
	for (size_t i = 0; i < count; ++i)
	{
		std::cout << i + 1 << ".";
		arr[i]->print();
	}
}

void Collection::allAreas() const
{
	for (size_t i = 0; i < count; ++i)
		std::cout << getAreaByIndex(i) << std::endl;
}

void Collection::allPerimeters() const
{
	for (size_t i = 0; i < count; ++i)
		std::cout << getPerimeterByIndex(i) << std::endl;
}

double Collection::getPerimeterByIndex(size_t index) const
{
	if (index >= count)
		throw "Out of range in collection!";
	return arr[index]->getPerimeter();
}

double Collection::getAreaByIndex(size_t index) const
{
	if (index >= count)
		throw "Out of range in collection!";
	return arr[index]->getArea();
}

double Collection::getincludesPointByIndex(size_t index, int x, int y) const
{
	if (index >= count)
		throw "Out of range in collection!";
	return arr[index]->includesPoint(x, y);
}

void Collection::takeTranslateInput(const String& input)
{
	String temp(input);

	temp.cutFront(strlen("translate "));

	double ind, x, y;
	size_t numberLen;
	if (isDigit(temp[0]))
	{
		temp.extractDouble(ind, numberLen);

		temp.cutFront(numberLen + 1);

		if (temp.firstWordIsSameAs("vertical="))
			temp.cutFront(strlen("vertical="));
		else
		{
			std::cout << "Invalid translate command input!" << std::endl;
			return;
		}

		temp.extractDouble(y, numberLen);

		temp.cutFront(numberLen + 1);

		if (temp.firstWordIsSameAs("horizontal="))
			temp.cutFront(strlen("horizontal="));
		else
		{
			std::cout << "Invalid translate command input!" << std::endl;
			return;
		}

		temp.extractDouble(x, numberLen);

		translation(y, x, int(ind - 1));
	}
	else
	{
		if (temp.firstWordIsSameAs("vertical="))
			temp.cutFront(strlen("vertical="));
		else
		{
			std::cout << "Invalid translate command input!" << std::endl;
			return;
		}


		temp.extractDouble(y, numberLen);

		temp.cutFront(numberLen + 1);

		if (temp.firstWordIsSameAs("horizontal="))
			temp.cutFront(strlen("horizontal="));
		else
		{
			std::cout << "Invalid translate command input!" << std::endl;
			return;
		}
		temp.extractDouble(x, numberLen);

		translation(y, x);
	}
}

void Collection::translation(double y, double x, int index)
{
	if (index != -1 && index >= count)
	{
		std::cout << "There is no shape with such index!" << std::endl;
		return;
	}
	if (index == -1)
	{
		for (size_t i = 0; i < count; ++i)
		{
			arr[i]->translate(y, x);
		}
		std::cout << "Translated all fugures." << std::endl;
		return;
	}
	arr[index]->translate(y, x);
	std::cout << "Translated (" << index + 1 << ")" << std::endl;
}

void Collection::create(const String& input)
{
	const double upperLimit = 10e5;
	const double lowerLimit = -upperLimit;
	const double eps = 1e-5;

	String temp(input);
	temp.reverse();
	temp.shorten(temp.getSize() - strlen("create "));
	temp.reverse();

	if (temp.getSize() == 0)
	{
		std::cout << "Invalid input!" << std::endl;
		return;
	}
	if (input.getStr() == nullptr)
		throw "Reading nullptr!";

	
	if (temp.firstWordIsSameAs("rectangle "))
	{
		double x, y, width, height;
		size_t numberLen = 0;
		
		switch (parseRectangle(temp, x, y, width, height, numberLen))
		{
		case -1: 
			validationMessage("rectangle");
			return;
		case 0:
			temp = "unknown";
		}
		if (x > upperLimit || x < lowerLimit || y > upperLimit || y < lowerLimit || width > upperLimit || width < eps || height > upperLimit || height < eps)
		{
			validationMessage("rectangle");
			return;
		}
		Rectangle toAdd(x, y, width, height, temp);
		addShape(toAdd);
		std::cout << "Successfully created rectangle! (" << count << ")" << std::endl;
	}
	else if (temp.firstWordIsSameAs("circle "))
	{
		double x, y, radius;
		size_t numberLen = 0;

		switch (parseCircle(temp, x, y, radius, numberLen))
		{
		case -1:
			validationMessage("circle");
			return;
		case 0:
			temp = "unknown";
		}
		if (x > upperLimit || x < lowerLimit || y > upperLimit || y < lowerLimit || radius > upperLimit || radius < eps)
		{
			validationMessage("circle");
			return;
		}
		Circle toAdd(x, y, radius, temp);
		addShape(toAdd);
		std::cout << "Successfully created circle! (" << count << ")" << std::endl;
	}
	else if (temp.firstWordIsSameAs("line "))
	{
		double x1, y1, x2, y2;
		size_t numberLen = 0;

		switch (parseLine(temp, x1, y1, x2, y2, numberLen))
		{
		case -1:
			validationMessage("line");
			return;
		case 0:
			temp = "unknown";
		}
		if (x1 > upperLimit || x1 < lowerLimit || y1 > upperLimit || y1 < lowerLimit || x2 > upperLimit || x2 < lowerLimit || y2 > upperLimit || y2 < lowerLimit)
		{
			validationMessage("line");
			return;
		}
		Line toAdd(x1, y1, x2, y2, temp);
		addShape(toAdd);
		std::cout << "Successfully created line! (" << count << ")" << std::endl;
	}
}

void Collection::printWithin(const String& input) const
{
	String temp(input);

	temp.reverse();
	temp.shorten(temp.getSize() - strlen("within "));
	temp.reverse();

	const double upperLimit = 10e5;
	const double lowerLimit = -upperLimit;
	const double eps = 1e-5;

	bool hasPrinted = false;
	if (temp.firstWordIsSameAs("rectangle"))
	{
		double x, y, width, height;
		size_t numberLen;
		switch (parseRectangle(temp, x, y, width, height, numberLen))
		{
		case -1:
			validationMessage("rectangle");
			return;
		case 0:
			temp = "unknown";
		}
		if (x > upperLimit || x < lowerLimit || y > upperLimit || y < lowerLimit || width > upperLimit || width < eps || height > upperLimit || height < eps)
		{
			validationMessage("rectangle");
			return;
		}
		for (size_t i = 0; i < count; ++i)
		{
			if (arr[i]->isWithinRectangle(x, y, width, height))
			{
				hasPrinted = true;
				arr[i]->print();
			}
		}
		if (!hasPrinted)
			std::cout << "No figures are located within rectangle " << x << " " << y << " " << width << " " << height << std::endl;
	}
	else if (temp.firstWordIsSameAs("circle"))
	{
		double x, y, radius;
		size_t numberLen;
		switch (parseCircle(temp, x, y, radius, numberLen))
		{
		case -1:
			validationMessage("circle");
			return;
		case 0:
			temp = "unknown";
		}
		if (x > upperLimit || x < lowerLimit || y > upperLimit || y < lowerLimit || radius > upperLimit || radius < eps)
		{
			validationMessage("circle");
			return;
		}
		for (size_t i = 0; i < count; ++i)
		{
			if (arr[i]->isWithinCircle(x, y, radius))
			{
				hasPrinted = true;
				arr[i]->print();
			}
		}
		if (!hasPrinted)
			std::cout << "No figures are located within circle " << x << " " << y << " " << radius << std::endl;
	}
	else 
		std::cout << "Invalid input for 'within'command!" << std::endl;
}

int Collection::parseRectangle(String& temp, double& x, double& y, double& width, double& height, size_t& numberLen) const
{
	temp.cutFront(strlen("rectangle "));
	temp.extractDouble(x, numberLen);
	if (!temp.cutFront(numberLen + 1))
		return -1;
	temp.extractDouble(y, numberLen);
	if (!temp.cutFront(numberLen + 1))
		return -1;
	temp.extractDouble(width, numberLen);
	if (!temp.cutFront(numberLen + 1))
		return -1;
	temp.extractDouble(height, numberLen);
	if (temp.cutFront(numberLen + 1))
		return 1;
	return 0;
}

int Collection::parseCircle(String& temp, double& x, double& y, double& radius, size_t& numberLen) const
{
	temp.cutFront(strlen("circle "));
	temp.extractDouble(x, numberLen);
	if (!temp.cutFront(numberLen + 1))
		return -1;
	temp.extractDouble(y, numberLen);
	if (!temp.cutFront(numberLen + 1))
		return -1;
	temp.extractDouble(radius, numberLen);
	if (temp.cutFront(numberLen + 1))
		return 1;
	return 0;
}

int Collection::parseLine(String& temp, double& x1, double& y1, double& x2, double& y2, size_t& numberLen) const
{
	temp.cutFront(strlen("line "));
	temp.extractDouble(x1, numberLen);
	if (!temp.cutFront(numberLen + 1))
		return -1;
	temp.extractDouble(y1, numberLen);
	if (!temp.cutFront(numberLen + 1))
		return -1;
	temp.extractDouble(x2, numberLen);
	if (!temp.cutFront(numberLen + 1))
		return -1;
	temp.extractDouble(y2, numberLen);
	if (temp.cutFront(numberLen + 1))
		return 1;
	return 0;
}

void Collection::parsePoint(String& temp, double& x, double& y, size_t numberLen)
{
	temp.cutFront(strlen("point in "));
	temp.extractDouble(x, numberLen);
	temp.cutFront(numberLen + 1);
	temp.extractDouble(y, numberLen);
}

void Collection::pointIn(const String& input)
{
	String temp(input);
	bool hasPrinted = false;
	if (temp.firstWordIsSameAs("point in"))
	{
		double x, y;
		size_t numberLen = 0;
		parsePoint(temp, x, y, numberLen);

		for (size_t i = 0; i < count; ++i)
		{
			if (arr[i]->includesPoint(x, y))
			{
				hasPrinted = true;
				arr[i]->print();
			}
		}
		if (!hasPrinted)
			std::cout << "None of the shapes includes the point (" << x << ", " << y << ")" << std::endl;
	}
	else
		std::cout << "Invalid input for 'point in' command!" << std::endl;
}

void Collection::validationMessage(const String& shape) const
{
	std::cout << "Invalid "<< shape << " data!" << std::endl;
}

void Collection::playFile(const String& input, String& name, String& copyFile, bool& openedFile)
{
	String temp(input);

	copyFile = "";
	name = "";

	temp.reverse();
	temp.shorten(temp.getSize() - strlen("open "));
	
	if (!temp.firstWordIsSameAs("gvs.")) // if the last four symbols are ".svg"
	{
		std::cout << "Invalid file name! File must be of \"svg\" type!" << std::endl;
		openedFile = false;
		return;
	}
	temp.reverse();

	name = temp;

	std::fstream file(name.getStr(), std::ios::app | std::ios::out | std::ios::in);

	if (!file.is_open())
	{
		std::cout << "File could not open..." << std::endl;
		return;
	}

	file.seekg(0, std::ios::end);
	size_t endPos = int(file.tellg());

	if (endPos == 0)
		std::cout << "This file is currently empty. Create at least one shape and save it in order to fill the file with information." << std::endl;
	else
	{
		std::cout << "File opened successfully!" << std::endl;
		loadFile(file, copyFile);
	}
	file.close();

	if (copyFile.getSize() == 0)
		copyFile += "<svg>\n";
}

void Collection::loadFile(std::fstream& file, String& copyFile)
{
	file.seekg(0, std::ios::beg);
	
	char buffer[1024];

	String keyWord = "<svg>";
	bool proceed = true;
	keyWord.reverse();
	while (!file.eof() && proceed)
	{
		file.getline(buffer, 1024);
		copyFile += buffer;

		copyFile.reverse();
		if (copyFile.firstWordIsSameAs(keyWord.getStr()))
		{
			copyFile.reverse();
			copyFile += "\n";
			proceed = false;
			break;
		}
		copyFile.reverse();
		copyFile += "\n";
	}
	
	bool validClosing = false;
	while (!file.eof() && !validClosing)
	{
		file.getline(buffer, 1024);
		parseSVGline(buffer, validClosing);
	}
}

void Collection::parseSVGline(char buff[], bool& validClosing)
{
	String temp(buff);
	if (temp.firstWordIsSameAs("</svg>"))
	{
		validClosing = true;
		return;
	}
	if (!temp.firstWordIsSameAs(" <") && !temp.firstWordIsSameAs("<"))
	{
		std::cout << "Invalid line of file!" << std::endl;
		return;
	}

	temp.cutFront(strlen(" <"));
	
	if (temp.firstWordIsSameAs("rect "))
	{
		temp.cutFront(strlen("rect "));

		if (!temp.firstWordIsSameAs("x=\""))
		{
			validationMessage("rectangle");
				return;
		}

		temp.cutFront(strlen("x=\""));

		double x, y, width, height;
		size_t numberLen;

		temp.extractDouble(x, numberLen);
		temp.cutFront(numberLen);

		if (!temp.firstWordIsSameAs("\" y=\""))
		{
			validationMessage("rectangle");
			return;
		}

		temp.cutFront(strlen("\" y=\""));
		temp.extractDouble(y, numberLen);
		temp.cutFront(numberLen);

		if (!temp.firstWordIsSameAs("\" width=\""))
		{
			validationMessage("rectangle, ");
			return;
		}

		temp.cutFront(strlen(" \"width=\""));
		temp.extractDouble(width, numberLen);
		temp.cutFront(numberLen);

		if (!temp.firstWordIsSameAs("\" height=\""))
		{
			validationMessage("rectangle");
			return;
		}

		temp.cutFront(strlen("\" height=\""));
		temp.extractDouble(height, numberLen);
		temp.cutFront(numberLen);

		if (!temp.firstWordIsSameAs("\" fill=\""))
		{
			validationMessage("rectangle");
			return;
		}

		temp.reverse();
		temp.shorten(temp.getSize() - strlen("\" fill=\""));
		
		if (!temp.firstWordIsSameAs(">/ \""))
		{
			validationMessage("rectangle");
			return;
		}
		temp.reverse();
		temp.shorten(temp.getSize() - strlen("\" />"));
		
		Rectangle toAdd(x, y, width, height, temp);
		addShape(toAdd);
	}
	else if (temp.firstWordIsSameAs("circle "))
	{
		temp.cutFront(strlen("circle "));

		if (!temp.firstWordIsSameAs("cx=\""))
		{
			validationMessage("circle");
			return;
		}

		temp.cutFront(strlen("cx=\""));


		double x, y, radius;
		size_t numberLen;

		temp.extractDouble(x, numberLen);
		temp.cutFront(numberLen);

		if (!temp.firstWordIsSameAs("\" cy=\""))
		{
			validationMessage("circle");
			return;
		}

		temp.cutFront(strlen("\" cy=\""));
		temp.extractDouble(y, numberLen);
		temp.cutFront(numberLen);

		if (!temp.firstWordIsSameAs("\" r=\""))
		{
			validationMessage("circle");
			return;
		}

		temp.cutFront(strlen("\" r=\""));
		temp.extractDouble(radius, numberLen);
		temp.cutFront(numberLen);

		if (!temp.firstWordIsSameAs("\" fill=\""))
		{
			validationMessage("circle");
			return;
		}

		temp.reverse();
		temp.shorten(temp.getSize() - strlen(" \"fill=\""));

		if (!temp.firstWordIsSameAs(">/ \""))
		{
			std::cout << "Invalid circle data!" << std::endl;
			return;
		}
		temp.reverse();
		temp.shorten(temp.getSize() - strlen("\" />"));

		Circle toAdd(x, y, radius, temp);
		addShape(toAdd);
	}
	else if (temp.firstWordIsSameAs("line "))
	{
		temp.cutFront(strlen("line "));

		if (!temp.firstWordIsSameAs("x1=\""))
		{
			validationMessage("line");
			return;
		}

		temp.cutFront(strlen("x1=\""));

		double x1, y1, x2, y2;
		size_t numberLen;

		temp.extractDouble(x1, numberLen);
		temp.cutFront(numberLen);

		if (!temp.firstWordIsSameAs("\" y1=\""))
		{
			validationMessage("line");
			return;
		}

		temp.cutFront(strlen("\" y1=\""));
		temp.extractDouble(y1, numberLen);
		temp.cutFront(numberLen);

		if (!temp.firstWordIsSameAs("\" x2=\""))
		{
			validationMessage("line");
			return;
		}

		temp.cutFront(strlen("\" x2=\""));
		temp.extractDouble(x2, numberLen);
		temp.cutFront(numberLen);

		if (!temp.firstWordIsSameAs("\" y2=\""))
		{
			validationMessage("line");
			return;
		}

		temp.cutFront(strlen("\" y2=\""));
		temp.extractDouble(y2, numberLen);
		temp.cutFront(numberLen);

		if (!temp.firstWordIsSameAs("\" fill=\""))
		{
			validationMessage("line");
			return;
		}

		temp.reverse();
		temp.shorten(temp.getSize() - strlen("\" fill=\""));

		if (!temp.firstWordIsSameAs(">/ \""))
		{
			validationMessage("line");
			return;
		}
		temp.reverse();
		temp.shorten(temp.getSize() - strlen("\" />"));

		Line toAdd(x1, y1, x2, y2, temp);
		addShape(toAdd);
	}
	else
	std::cout << "A type of shape is either not supported, or invalid..." << std::endl;
}

void Collection::writeToFile(const String& name, String& copyFile)
{
	//opening the file in writing mode without append flag in order to delete the old information
	std::ofstream out(name.getStr()); 
	
	out << copyFile;
	for (size_t i = 0; i < count; ++i)
		arr[i]->writeSVGline(out);
	copyFile = "</svg>";
	out << copyFile;
	out.close();
	std::cout << "Changes saved to " << name << " successfully!" << std::endl;
	reset();
}

void Collection::Menu()
{
	std::cout << "Welcome to the command menu! To view the instructions on how to use the application, type \"instructions\"." << std::endl;

	bool openedFile = false;
	String copyFile, name;

	while (true)
	{
		std::cout << ">";
		String input;

		input.getLine(std::cin);
		std::cin.clear();
		if (input.firstWordIsSameAs("instructions") && input.getSize() == strlen("instructions"))
			instructions();
		else if (!openedFile && input.firstWordIsSameAs("open "))
		{
			openedFile = true;
			playFile(input, name, copyFile, openedFile);
		}
		else if (openedFile && input.firstWordIsSameAs("print") && input.getSize() == strlen("print"))
			printAll();
		else if (openedFile && input.firstWordIsSameAs("create "))
			create(input);
		else if (openedFile && input.firstWordIsSameAs("erase "))
			toErase(input);
		else if (openedFile && input.firstWordIsSameAs("translate "))
			takeTranslateInput(input);
		else if (openedFile && input.firstWordIsSameAs("within "))
			printWithin(input);
		else if (openedFile && input.firstWordIsSameAs("point in "))
			pointIn(input);
		else if (openedFile && input.firstWordIsSameAs("areas") && input.getSize() == strlen("areas"))
			allAreas();
		else if (openedFile && input.firstWordIsSameAs("pers") && input.getSize() == strlen("pers"))
			allPerimeters();
		else if (openedFile && input.firstWordIsSameAs("save") && input.getSize() == strlen("save"))
		{
			writeToFile(name, copyFile);
			openedFile = false;
		}
		else if (input.firstWordIsSameAs("exit") && input.getSize() == strlen("exit"))
			return;
		else if (input.getSize() > 0)
			std::cout << "Invalid command. Please try again!" << std::endl;
	}
}

void Collection::instructions()
{
	std::cout << "You can perform the following operations: " << std::endl;
	std::cout << "	- Open a file (type a name of a \".svg\" file (if it doesn't exist, it is going to be generated)" << std::endl;
	std::cout << "			example: \"open figures.svg\"" << std::endl;
	std::cout << "	- Print all present shapes (type \"print\")" << std::endl;
	std::cout << "	- Create a new shape (you can choose between a rectangle, a circle, or a line) " << std::endl;
	std::cout << "		*to create a rectangle, type: \"rectangle <x> <y> <width> <height> <color>\"" << std::endl;
	std::cout << "			example: \"rectangle 100 100 30 40 blue\"" << std::endl;
	std::cout << "		*to create a circle, type: \"circle <cx> <cy> <radius> <color>\"" << std::endl;
	std::cout << "			example: \"circle 10 20 14 red\"" << std::endl;
	std::cout << "		*to create a line, type: \" line <x1> <y1> <x2> <y2> <color>\"" << std::endl;
	std::cout << "			example: \"line 0 1 3 9 white\"" << std::endl;
	std::cout << "	- Erase a certain shape by its index (if there are 3 shapes, the index of the first one is 1)" << std::endl;
	std::cout << "			example: \"erase 2\"" << std::endl;
	std::cout << "	- Translate a ceratain shape / all shapes" << std::endl;
	std::cout << "		*to translate a certain shape, type \"translate <index> vertical=<y> horizontal=<x>\"" << std::endl;
	std::cout << "			example: \"translate 3 vertical=10 horizontal=100\"" << std::endl;
	std::cout << "		*to translate all shapes, simply don't type an index" << std::endl;
	std::cout << "			exampe: \"translate vertical=90 horizontal=42\"" << std::endl;
	std::cout << "	- Check how many of the present shapes are included in a chosen circle/rectangle" << std::endl;
	std::cout << "		option 1: \"within rectangle <x> <y> <width> <height>\"" << std::endl;
	std::cout << "		option 2: \"within circle <cx> <cy> <radius>\"" << std::endl;
	std::cout << "	- Check how many of the present shapes include a chosen point" << std::endl;
	std::cout << "			example: \"point in <x> <y>\"" << std::endl;
	std::cout << "	- Print the areas of all figures (a line has an area of 0 square units)" << std::endl;
	std::cout << "		(type \"areas\")" << std::endl;
	std::cout << "	- Print the perimeters of all figures (the perimeter of a line is its length)" << std::endl;
	std::cout << "		(type \"pers\")" << std::endl;
	std::cout << "	- Save the current changes and close the opened file (type \"save\")" << std::endl;
	std::cout << "	- Exit (doesn't save any changes, if you hadn't save the beforehand)" << std::endl;
	std::cout << "		(type \"exit\")" << std::endl;
	std::cout << "You cannot perform shape operations if you haven't opened a file\nand you cannot open a new file before you have saved the current one!" << std::endl;
}
