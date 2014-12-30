#include "String.h"

void String::init()
{
	string = NULL;
	length = 0;
}

void String::clear()
{
	delete[] string;
	string = NULL;
	length = 0;
}

void String::copyFrom(const String& other)
{
	string = new char[other.length + 1];
	length = other.length;

	if (!length)
	{
		strcpy_s(string, 1, "");
	}
	else
		strcpy_s(string, length + 1, other.string);
}

void String::copyFrom(const char* other)
{
	if (!other)
	{
		string = new char;
		strcpy_s(string, 1, "");
		length = 0;
		return;
	}
	size_t len = strlen(other);
	length = len;
	string = new char[len + 1];
	strcpy_s(string, len + 1, other);
}

size_t String::getLength() const
{
	return length;
}


String::String()
{
	init();
}

String::String(const String& other)
{
	copyFrom(other);
}

String::String(const char* other)
{
	copyFrom(other);
}

String::~String()
{
	clear();
}
String& String::operator=(const String& other)
{
	if (this != &other)
	{
		clear();
		copyFrom(other);
	}
	return *this;
}

String& String::operator=(const char* other)
{
	clear();
	copyFrom(other);
	return *this;
}

String& String::operator+=(const char& chr)
{
	char* buffer = new char[length + 2];

	if (!string)
	{
		buffer[0] = chr;
		buffer[1] = '\0';
		string = new char[length + 2];
		strcpy_s(string, length + 2, buffer);
		length++;
		return *this;
	}

	strcpy_s(buffer, length + 2, string);
	buffer[length] = chr;
	buffer[length + 1] = '\0';
	clear();
	copyFrom(buffer);
	delete[] buffer;
	return *this;
}

bool String::operator==(const String& other) const
{
	if (length != other.length)
		return false;

	for (size_t i = 0; i < length; i++)
	{
		if (string[i] != other.string[i])
			return false;
	}
	return true;
}

bool String::operator!=(const String& other) const
{
	return !(*this == other);
}

char String::operator[](size_t index) const
{
	if (index > length)
		throw "invalid index";
	return string[index];
}

ostream& operator<<(ostream& out, const String& string)
{
	if (string.string)
		out << string.string;
	return out;
}

