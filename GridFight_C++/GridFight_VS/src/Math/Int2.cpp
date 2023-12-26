#include "Int2.h"

#include <string>

int2::int2() : x(0), y(0)
{

}

int2::int2(const int x, const int y) : x(x), y(y)
{

}

unsigned int int2::ManhattanDistance(const int2 other) const
{
	return abs(x - other.x) + abs(y - other.y);

}

int2 int2::operator +(const int2 other) const
{
	return { x + other.x, y + other.y };
}

int2 int2::operator -(const int2 other) const
{
	return { x - other.x, y - other.y };
}

int2 int2::operator *(const int2 other) const
{
	return { x * other.x, y * other.y };
}

int2 int2::operator *(const int other) const
{
	return { x * other, y * other };
}

int2 int2::operator /(const int2 other) const
{
	return { x / other.x, y / other.y };
}

int2 int2::operator /(const int other) const
{
	return { x / other, y / other };
}

void int2::operator +=(const int2 other)
{
	x += other.x;
	y += other.y;
}

void int2::operator -=(const int2 other)
{
	x -= other.x;
	y -= other.y;
}

void int2::operator *=(const int2 other)
{
	x *= other.x;
	y *= other.y;
}

void int2::operator *=(const int other)
{
	x *= other;
	y *= other;
}

void int2::operator /=(const int2 other)
{
	x /= other.x;
	y /= other.y;
}

void int2::operator /=(const int other)
{
	x /= other;
	y /= other;
}

bool int2::operator==(const int2 other) const
{
	return x == other.x && y == other.y;
}

int2::operator std::string() const
{
	std::string result = "(";
	result += std::to_string(x);
	result += "|";
	result += std::to_string(y);
	result += ")";
	return result;
}


std::ostream& operator<<(std::ostream& stream, const int2 i)
{
	stream << "(" << i.x << "|" << i.y << ")";
	return stream;
}
