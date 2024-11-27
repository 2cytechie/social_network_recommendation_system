#pragma once

#include<cmath>

class Vector2 {
public:
	float x = 0;
	float y = 0;

public:
	Vector2() = default;
	~Vector2() = default;

	Vector2(float x, float y)
		:x(x), y(y) {
	}

	float length() {
		return sqrt(x * x + y * y);
	}

	Vector2 normalize() {
		float len = length();
		if (len == 0) {
			return Vector2(0, 0);
		}
		return Vector2(x / len, y / len);
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

	float operator* (const Vector2& vec) const {
		return x * vec.x + y * vec.y;
	}

	Vector2 operator*(const float val) const {
		return Vector2(val * x, val * y);
	}

	void operator*=(float val) {
		x *= val, y *= val;
	}

};
