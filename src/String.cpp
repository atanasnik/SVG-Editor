#include "String.h"
#include <cstring>
#pragma warning (disable : 4996)
String::String() : capacity(8)
{
	str = new char[capacity];
	str[0] = '\0';
	size = 0;
}

String::String(const char* str)
{
	size = strlen(str);
	capacity = size + 1;
	this->str = new char[strlen(str) + 1];
	strcpy(this->str, str);
}
void String::setString(const String& str)
{
	*this = str;
}
String::String(const String& other)
{
	copyFrom(other);
}
String& String::operator=(const String& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}
void String::copyFrom(const String& other)
{
	size = other.size;
	capacity = other.capacity;
	str = new char[strlen(other.str) + 1];
	strcpy(str, other.str);
}
void String::free()
{
	delete[] str;
}
String::~String()
{
	free();
}

size_t String::getCapacity() const
{
	return capacity;
}
size_t String::getSize() const
{
	return size;
}
const char* String::getStr() const
{
	return str;
}
char& String::operator[](size_t index)
{
	if (index >= size)
		throw "Invalid index";

	return str[index];
}

char String::operator[](size_t index) const
{
	if (index >= size)
		throw "Invalid index";

	return str[index];
}
std::ostream& operator<<(std::ostream& out, const String& s)
{
		out << s.str;
	return out;
}
std::istream& operator>>(std::istream& in, String& s)
{
	char temp[1024];
	in >> temp;
	s.setString(temp);
	return in;
}
bool operator==(const String& a, const String& b)
{
	return (!strcmp(a.getStr(), b.getStr()));
}
size_t wholeLen(double num)
{
	num > 0 ? num = num : num = -num;
	size_t count = 0;
	int whole = num / 1;
	while (whole > 0)
	{
		whole /= 10;
		++count;
	}
	return count;
}
void String::resize()
{
	capacity *= 2;
	char* resizedArray = new char[capacity];

	strcpy(resizedArray, str);
	
	delete[] str;
	str = resizedArray;
}
String& String::operator+=(const String& other)
{
	while (size + other.getSize() >= capacity - 1)
		resize();
	
	strcat(str, other.str);

	size = strlen(getStr());

	return *this;
}

void String::getLine(std::istream& in)
{
	delete[] str;
	char buff[1024];

	in.getline(buff, 1024, '\n');
	size_t len = strlen(buff);
	str = new char[len + 1];

	for (size_t i = 0; i < len; ++i)
		str[i] = buff[i];
	str[len] = '\0';
	size = len;
}

bool String::firstWordIsSameAs(const char* str) const
{
	size_t length = strlen(str);
	if (length == 0)
		return false;
	for (size_t i = 0; i < length; ++i)
	{
		if (getStr()[i] != str[i])
			return false;
	}
	return true;
}

void String::reverse()
{
	for (int i = 0; i < size / 2; ++i)
		swap(str[i], str[size - i - 1]);
}

bool String::shorten(const size_t& index)
{
	if (size <= 1 || index > 10e3)
		return false;
	if (index > size)
		throw "Out of range!";

	str[index] = '\0';
	size = index;
	char* temp = new char[size + 1];
	strcpy(temp, str);

	delete[] str;
	str = temp;
	temp = nullptr;
	return true;
}

void String::extractDouble(double& num, size_t& count)
{
	count = 0;
	double whole = 0;
	int decimalPart = 0;
	bool passedPoint = false;
	bool isNegative = false;
	size_t decimalPartLen = 0;
	for (size_t i = 0; str[i] != ' ' && str[i] != '\0' && str[i] != '\n' && str[i] != '\"'; ++i)
	{
		if (str[0] == '-' && i == 0)
		{
			isNegative = true;
			++count;
			continue;
		}
		if (isDigit(str[i]) && !passedPoint)
		{
			whole = whole * 10 + str[i] - '0';
			++count;
		}
		else if (str[i] == '.' && i > 0 && i < size - 1)
		{
			passedPoint = true;
			++count;
		}
		else if (isDigit(str[i]) && passedPoint)
		{
			decimalPart = decimalPart * 10 + str[i] - '0';
			++count;
			++decimalPartLen;
		}
		else
		{
			std::cout << "Invalid decimal number input!" << std::endl;
			return;
		}
	}
	
	double toDouble = decimalPart;
	for (size_t i = 0; i < decimalPartLen; ++i)
		toDouble *= 1e-1;

	num = toDouble;
	num += whole;
	if (isNegative)
		num *= -1;
}

bool String::cutFront(const size_t& index)
{
	reverse();
	if (shorten(size - index))
	{
		reverse();
		return true;
	}
	reverse();
	return false;
}

void swap(char& a, char& b)
{
	char temp = 0;
	temp = a;
	a = b;
	b = temp;
}

bool isDigit(const char& s)
{
	return s >= '0' && s <= '9';
}

size_t intLen(int num)
{
	size_t count = 0;
	while (num != 0)
	{
		num /= 10;
		++count;
	}
	return count;
}

String::String(String&& other)
{
	str = other.str;
	size = other.size;
	capacity = other.capacity;
	other.str = nullptr;
}

String& String::operator=(String&& other)
{
	if (this != &other)
	{
		free();
		str = other.str;
		other.str = nullptr;
		size = other.size;
		capacity = other.capacity;
	}
	return *this;
}
