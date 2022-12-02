#include "pch.h"
#include "Light.h"

void Light::SetAmbient(const Math::Color& ambient)
{
	this->ambient = ambient;
}

void Light::SetDiffuse(const Math::Color& diffuse)
{
	this->diffuse = diffuse;
}

void Light::SetSpecular(const Math::Color& specular)
{
	this->specular = specular;
}
