#pragma once

#include<cmath>

class Vector2 {
public:
	int x = 0;
	int y = 0;

public:
	Vector2() = default;
	~Vector2() = default;

	Vector2(int x, int y)
		:x(x), y(y) {
	}

	Vector2 operator+(const Vector2& vec) const {
		return Vector2(x + vec.x, y + vec.y);
	}

	void operator+=(const Vector2& vec) {
		x += vec.x, y += vec.y;
	}

	void operator-=(const Vector2& vec) {
		x -= vec.x, y -= vec.y;
	}

	Vector2 operator-(const Vector2& vec) const {
		return Vector2(x - vec.x, y - vec.y);
	}

	int operator* (const Vector2& vec) const {
		return x * vec.x + y * vec.y;
	}

	Vector2 operator*(const int val) const {
		return Vector2(val * x, val * y);
	}

	void operator*=(int val) {
		x *= val, y *= val;
	}

};
