#pragma once
#include "Vector3.h"

class Light
{
public:
	virtual ~Light() = default;

	virtual Color ComputeLightColor(const Math::Vector3& pos, const Math::Vector3& normal) const = 0;

	void SetAmbient(const Color& ambient);
	void SetDiffuse(const Color& diffuse);
	void SetSpecular(const Color& specular);

protected:

	Color ambient = WHITE;
	Color diffuse = WHITE;
	Color specular = WHITE;
};

