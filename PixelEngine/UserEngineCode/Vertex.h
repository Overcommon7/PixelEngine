#pragma once
#include "Vector3.h"
#include "Vector2.h"
#include "Light.h"

class Vertex
{
public:
	Math::Vector3 pos;
	Math::Vector3 worldPos;
	Math::Vector3 worldNormal;
	Math::Vector3 normal;
	Math::Color color;

	Vertex() : pos({}), worldPos({}), worldNormal({}), normal({}), color(WHITE) {}
	Vertex(const Math::Vector3& Pos, const Math::Color& c = WHITE, const Math::Vector3& WorldPos = Math::Vector3(), const Math::Vector3& WorldNormal = Math::Vector3(), const Math::Vector3& Normal = Math::Vector3()) : pos(Pos), worldPos(WorldPos), worldNormal(WorldNormal), normal(Normal), color(c) {}
	Vertex(const Math::Vector2& Pos, const Math::Color& c = WHITE, const Math::Vector3& WorldPos = Math::Vector3(), const Math::Vector3& WorldNormal = Math::Vector3(), const Math::Vector3& Normal = Math::Vector3()) : pos({ Pos.x, Pos.y, 0 }), worldPos(WorldPos), worldNormal(WorldNormal), normal(Normal), color(c) {}

	Vertex(const Vertex& v) = default;
	Vertex& operator=(const Vertex& v) = default;

	Vertex Lerp(const Vertex& v, const float& t, bool lerpNorm = false) const
	{
		Vertex ver = Vertex();
		ver.pos = pos.Lerp(v.pos, t);
		ver.normal = normal.Lerp(v.pos, t);
		ver.color = color.Lerp(v.color, t);
		if (lerpNorm)
		{
			ver.normal = normal.Lerp(v.pos, t);
			ver.normal = ver.normal.Normalize();
		}
		return ver;
	}
};

