#pragma once
#include "pch.h"
#include "Utilities.h"

namespace Math
{
	class Vector3
	{
	public:
		float x;
		float y;
		float z;

		Vector3() : x(0), y(0), z(0) {}
		Vector3(const float& X, const float& Y, const float& Z) : x(X), y(Y), z(Z) {}
		Vector3(std::initializer_list<float>& list) : x(0), y(0), z(0)
		{
			if (list.size() == 1)
			{
				x = *list.begin();
				y = *list.begin();
				z = *list.begin();
				return;
			}
			int i = 0;
			for (const auto& item : list)
			{
				i++;
				if (i == 1) x = item;
				else if (i == 2) y = item;
				else if (i == 3) z = item;
				else return;
			}
		}
		Vector3(const vector<float>& values)
		{
			if (values.size() < 3)
			{
				*this = Vector3();
				return;
			}
			x = values[0];
			y = values[1];
			z = values[2];
		}
		operator rVector3() const { return rVector3(x, y, z); }
		Vector3(const Vector3& vec) = default;
		Vector3& operator=(const Vector3& vec) = default;
		Vector3& operator=(const rVector3& vec) { x = vec.x; y = vec.y;	z = vec.z; return *this; }
		Vector3(const rVector3& vec) : x(vec.x), y(vec.y), z(vec.z) {}
		bool operator==(const Vector3& vec) const { return Utils::Equals(x, vec.x) && Utils::Equals(y, vec.y) && Utils::Equals(z, vec.z); }
		bool operator!=(const Vector3& vec) const { return !(Utils::Equals(x, vec.x) && Utils::Equals(y, vec.y) && Utils::Equals(z, vec.z)); }
		Vector3 operator+(const Vector3& vec) const { return Vector3(this->x + vec.x, this->y + vec.y, this->z + vec.z); }
		Vector3 operator-(const Vector3& vec) const { return Vector3(this->x - vec.x, this->y - vec.y, this->z - vec.z); }
		Vector3 operator/(const float& f) const { if (f == 0) return *this; return Vector3(this->x / f, this->y / f, this->z / f); }
		Vector3 operator*(const float& f) const { return Vector3(this->x * f, this->y * f, this->z * f); }

		float Magnitude() const
		{
			return sqrtf((x * x) + (y * y) + (z * z));
		}
		float MagnitudeSquared() const
		{
			const float mag = Magnitude();
			return mag * mag;
		}
		float DotProduct(const Vector3& vec) const
		{
			return (vec.x * this->x) + (vec.y * this->y) + (vec.z * this->z);
		}
		Vector3 Normalize() const
		{
			const float mag = Magnitude();
			return Vector3(x / mag, y / mag, z / mag);
		}
		Vector3 CrossProduct(const Vector3& w) const
		{
			return Vector3(
				(this->y * w.z) - (w.y * this->z),
				(this->z * w.x) - (w.z * this->x),
				(this->x * w.y) - (w.x * this->y));
		}
		Vector3 Lerp(const Vector3& vec, const float& t) const
		{
			return Vector3(
				std::lerp(x, vec.x, t),
				std::lerp(y, vec.y, t),
				std::lerp(z, vec.z, t));
		}

	};

}





