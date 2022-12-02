#pragma once

namespace Math
{
	class Color
	{
	public:
		float r;
		float g;
		float b;
		float a;

		Color() : r(0), g(0), b(0), a(1) {}
		Color(const Color& c) = default;
		Color(const rColor& c);
		Color(const float& r, const float& g, const float& b, const float& a = 1);
		Color(std::initializer_list<float> list);
		Color& operator= (const Color& c) = default;
		Color& operator= (const rColor& c);
		operator rColor() const;

		Color operator*(const Color& c) const;
		Color operator-(const Color& c) const;
		Color operator+(const Color& c) const;
		Color operator*(const rColor& c) const;
		Color operator-(const rColor& c) const;
		Color operator+(const rColor& c) const;
		Color operator*(const float& c) const;
		Color operator-(const float& c) const;
		Color operator+(const float& c) const;

		void operator*=(const Color& c);
		void operator-=(const Color& c);
		void operator+=(const Color& c);
		void operator*=(const rColor& c);
		void operator-=(const rColor& c);
		void operator+=(const rColor& c);
		void operator*=(const float& c);
		void operator-=(const float& c);
		void operator+=(const float& c);
	};
}


