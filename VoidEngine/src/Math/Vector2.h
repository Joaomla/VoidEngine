#pragma once
#include <iostream>

struct Vector2
{
	float x, y = 0;

	Vector2()
		: x(0.0f), y(0.0f)
	{}

	Vector2(float x, float y)
		: x(x), y(y)
	{}

	Vector2 operator+(Vector2 const& v)
	{
		return Vector2(x + v.x, y + v.y);
	}

	Vector2 operator+=(Vector2 const& v)
	{
		x += v.x;
		y += v.y;

		return *this;
	}

	Vector2 operator-(Vector2 const& v)
	{
		return Vector2(x - v.x, y - v.y);
	}

	Vector2 operator-=(Vector2 const& v)
	{
		x -= v.x;
		y -= v.y;

		return *this;
	}

	Vector2 operator*(float v)
	{
		return Vector2(x * v, y * v);
	}

	friend std::ostream& operator<<(std::ostream& stream, Vector2 const& v)
	{
		stream << "(" << v.x << "," << v.y << ")";
		return stream;
	}
};