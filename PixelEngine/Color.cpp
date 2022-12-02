#include "pch.h"
#include "Color.h"

namespace Math
{
	Color::Color(const rColor& c)
	{
		r = c.r / 255.f; g = c.g / 255.f; b = c.b / 255.f; a = 1;
	}

	Color::Color(const float& R, const float& G, const float& B, const float& A)
	{
		r = R / 255.f; g = G / 255.f; b = B / 255.f; a = 1;
	}

	Color& Color::operator=(const rColor& c)
	{

		r = (float)c.r / 255.f; g = (float)c.g / 255.f; b = (float)c.b / 255.f; a = 1;
		return *this;
	}
	Color::operator rColor()
	{
		return Color(
			(unsigned char)std::min(r * 255.f, 255.f),
			(unsigned char)std::min(g * 255.f, 255.f),
			(unsigned char)std::min(b * 255.f, 255.f),
			(unsigned char)std::min(a * 255.f, 255.f));
	}
	Color Color::operator*(const Color& c) const
	{
		return Color(
			std::min(c.r * r, 1.f),
			std::min(c.g * g, 1.f),
			std::min(c.b * b, 1.f),
			1);
		
	}
	Color Color::operator-(const Color& c) const
	{
		return Color(
			std::max(c.r - r, 0.f),
			std::max(c.g - g, 0.f),
			std::max(c.b - b, 0.f),
			1);
	}
	Color Color::operator+(const Color& c) const
	{
		return Color(
			std::min(c.r + r, 1.f),
			std::min(c.g + g, 1.f),
			std::min(c.b + b, 1.f),
			1);
	}
	Color Color::operator*(const rColor& c)	const
	{
		return Color(
			std::min(((float)c.r / 255) * r, 1.f),
			std::min(((float)c.g / 255) * g, 1.f),
			std::min(((float)c.b / 255) * b, 1.f),
			1);
	}
	Color Color::operator-(const rColor& c)	const
	{
		return Color(
			std::max(((float)c.r / 255) - r, 0.f),
			std::max(((float)c.g / 255) - g, 0.f),
			std::max(((float)c.b / 255) - b, 0.f),
			1);
	}
	Color Color::operator+(const rColor& c)	const
	{
		return Color(
			std::min(((float)c.r / 255) + r, 1.f),
			std::min(((float)c.g / 255) + g, 1.f),
			std::min(((float)c.b / 255) + b, 1.f),
			1);
	}
	void Color::operator*=(const Color& c)
	{
		Color temp = Color(
			std::min(c.r * this->r, 1.f),
			std::min(c.g * this->g, 1.f),
			std::min(c.b * this->b, 1.f),
			1);
		*this = temp;
	}
	void Color::operator-=(const Color& c)
	{
		Color temp = Color(
			std::max(c.r - r, 0.f),
			std::max(c.g - g, 0.f),
			std::max(c.b - b, 0.f),
			1);
		*this = temp;
	}
	void Color::operator+=(const Color& c)
	{
		Color temp = Color(
			std::min(c.r + r, 1.f),
			std::min(c.g + g, 1.f),
			std::min(c.b + b, 1.f),
			1);
		*this = temp;
	}
	void Color::operator*=(const rColor& c)
	{
		Color temp = Color(
			std::min(((float)c.r / 255) * r, 1.f),
			std::min(((float)c.g / 255) * g, 1.f),
			std::min(((float)c.b / 255) * b, 1.f),
			1);
		*this = temp;
	}
	void Color::operator-=(const rColor& c)
	{
		Color temp = Color(
			std::max(((float)c.r / 255) - r, 0.f),
			std::max(((float)c.g / 255) - g, 0.f),
			std::max(((float)c.b / 255) - b, 0.f),
			1);
		*this = temp;
	}
	void Color::operator+=(const rColor& c)
	{
		Color temp = Color(
			std::min(((float)c.r / 255) + r, 1.f),
			std::min(((float)c.g / 255) + g, 1.f),
			std::min(((float)c.b / 255) + b, 1.f),
			1);
		*this = temp;
	}
}
