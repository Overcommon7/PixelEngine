#pragma once
#include "pch.h"

namespace Math
{
	class Vector2
	{
	public:
		float x;
		float y;

		Vector2() : x(0), y(0) {}
		Vector2(const float& X, const float& Y) : x(X), y(Y) {}
		Vector2(std::initializer_list<float>& list) : x(0), y(0)
		{
			if (list.size() == 1)
			{
				x = *list.begin();
				y = *list.begin();
				return;
			}
				
			int i = 0;
			for (const auto& item : list)
			{
				i++;
				if (i == 1) x = item;
				else if (i == 2) y = item;
				else return;
			}
		}
		Vector2(const Vector2& vec) = default;
		Vector2& operator=(const Vector2 & vec) = default;
		Vector2& operator=(const rVector2& vec) { x = vec.x; y = vec.y; return *this; }
		Vector2(const rVector2& vec) { x = vec.x; y = vec.y; }
		operator rVector2() const { return rVector2(x, y); }
		bool operator==(const Vector2& vec) const { return vec.x == this->x && vec.y == this->y; }
		bool operator!=(const Vector2& vec) const { return vec.x != this->x || vec.y != this->y; }
		Vector2 operator+(const Vector2& vec) const { return Vector2(this->x + vec.x, this->y + vec.y); }
		Vector2 operator-(const Vector2& vec) const { return Vector2(this->x - vec.x, this->y - vec.y); }
		Vector2 operator/(const float& f) const { if (f == 0) return *this; return Vector2(this->x / f, this->y / f); }
		Vector2 operator*(const float& f) const { return Vector2(this->x * f, this->y * f); }

		float Magnitude() const
		{
			return sqrtf((x * x) + (y * y));
		}
		float MagnitudeSquared() const
		{
			const float mag = Magnitude();
			return mag * mag;
		}
		float DotProduct(const Vector2& vec) const
		{
			return (vec.x * this->x) + (vec.y * this->y);
		}
		Vector2 Normalize() const
		{
			const float mag = Magnitude();
			return Vector2(x / mag, y / mag);			
		}
	};
};


