#pragma once

#include <iostream>
class String
{
private:
	char* str;
	size_t size;
	size_t capacity;

	void copyFrom(const String& other);
	void free();
public:
	String();
	String(const char*);
	String(const String&);
	String& operator=(const String& other);
	~String();

	size_t getCapacity() const;
	size_t getSize() const;
	char& operator[](size_t index);
	char operator[](size_t index) const;
	const char* getStr() const;
	friend std::ostream& operator<<(std::ostream& os, const String& s);
	friend std::istream& operator>>(std::istream&, String& s);
	void setString(const String& str);

	void resize();
	String& operator+=(const String& other);
	void getLine(std::istream& in);

	bool firstWordIsSameAs(const char* str) const;
	void reverse();
	bool shorten(const size_t& index);
	bool cutFront(const size_t& index);
	void extractDouble(double& num, size_t& count);

	String(String&& other);
	String& operator=(String&& other);
};
bool operator==(const String&, const String&);
void swap(char& a, char& b);
bool isDigit(const char&);
size_t intLen(int);