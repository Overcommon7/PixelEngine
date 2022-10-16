#pragma once
#include "Vector3.h"
#include "Vector2.h"

class Vertex
{
public:
	Math::Vector3 pos;
	Color color;

	Vertex() : pos({}), color(WHITE) {}
	Vertex(const Math::Vector3& Pos, const Color& c = WHITE) : pos(Pos), color(c) {}
	Vertex(const Math::Vector2& Pos, const Color& c = WHITE) : pos({ Pos.x, Pos.y, 0 }), color(c) {}
	Vertex(const Vertex& v) = default;
	Vertex& operator=(const Vertex& v) = default;

	Math::Vector3 GetColorAsVector3() const
	{
		return Math::Vector3(
			(float)color.r,
			(float)color.g,
			(float)color.b
		);
	}
};

