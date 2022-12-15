#pragma once
#include "Vector3.h"


class Light
{
public:
	virtual ~Light() = default;

	virtual Math::Color ComputeLightColor(const Math::Vector3& pos, const Math::Vector3& normal) const = 0;

	void SetAmbient(const Math::Color& ambient);
	void SetDiffuse(const Math::Color& diffuse);
	void SetSpecular(const Math::Color& specular);

protected:

	Math::Color ambient = WHITE;
	Math::Color diffuse = WHITE;
	Math::Color specular = WHITE;
};

