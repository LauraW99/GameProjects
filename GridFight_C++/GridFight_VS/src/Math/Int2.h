#pragma once
#include <iostream>

struct int2
{
public:
	int x;
	int y;

	int2();
	int2(int x, int y);

	unsigned int ManhattanDistance(const int2 other) const;


	int2 operator +(const int2 other) const;
	int2 operator -(const int2 other) const;
	int2 operator *(const int2 other) const;
	int2 operator *(const int other) const;
	int2 operator /(const int2 other) const;
	int2 operator /(const int other) const;
	void operator +=(const int2 other);
	void operator -=(const int2 other);
	void operator *=(const int2 other);
	void operator *=(const int other);
	void operator /=(const int2 other);
	void operator /=(const int other);
	bool operator ==(const int2 other) const;

	explicit operator std::string() const;

	friend std::ostream& operator<<(std::ostream& stream, int2 i);
};