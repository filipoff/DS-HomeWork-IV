#pragma once

template < class T1, class T2 >

struct Pair
{
	T1 first;
	T2 second;
	Pair() : first(), second() {}
	Pair(const T1& first, const T2& second) : first(first), second(second) {}
	Pair(const Pair<T1, T2>& other)
	{
		first = other.first;
		second = other.second;
	}
	Pair& operator=(const Pair<T1, T2>& other)
	{
		if (this != &other)
		{
			first = other.first;
			second = other.second;
		}
		return *this;
	}
};

struct Attribute
{
	Pair<String, String> data;
	Attribute() : data(Pair<String,String>::Pair()) {}
	Attribute(const String& first, const String& second) : data(first, second) {}
	Attribute(const Attribute& other)
	{
		data.first = other.data.first;
		data.second = other.data.second;
	}
	Attribute& operator=(const Attribute& other)
	{
		if (this != &other)
		{
			data.first = other.data.first;
			data.second = other.data.second;
		}
		return *this;
	}
};