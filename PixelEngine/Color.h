#pragma once

namespace Math
{
	class Color
	{
		float r;
		float g;
		float b;
		float a;

		Color() = default;
		Color(const Color& c) = default;
		Color(const rColor& c);
		Color(const float& r, const float& g, const float& b, const float& a = 1);
		Color& operator= (const Color& c) = default;
		Color& operator= (const rColor& c);
		operator rColor();

		Color operator*(const Color& c) const;
		Color operator-(const Color& c) const;
		Color operator+(const Color& c) const;
		Color operator*(const rColor& c) const;
		Color operator-(const rColor& c) const;
		Color operator+(const rColor& c) const;

		void operator*=(const Color& c);
		void operator-=(const Color& c);
		void operator+=(const Color& c);
		void operator*=(const rColor& c);
		void operator-=(const rColor& c);
		void operator+=(const rColor& c);
	};
}


