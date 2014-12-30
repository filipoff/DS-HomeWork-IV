#pragma once
#include "Utils.h"

class String
{
private:
	char* string;
	size_t length;

private:
	void copyFrom(const String& other);
	void copyFrom(const char* other);


public:
	String();
	String(const char* other);
	String(const String& other);
	String& operator=(const String& other);
	String& operator=(const char* other);
	String& operator+=(const char& chr);
	bool operator==(const String& other) const;
	bool operator!=(const String& other) const;
	friend ostream& operator<<(ostream& out, const String& string);
	char operator[](size_t index) const;
	~String();
	void clear();
	size_t getLength() const;
};