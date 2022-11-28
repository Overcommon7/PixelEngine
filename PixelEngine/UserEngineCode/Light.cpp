#include "pch.h"
#include "Light.h"

void Light::SetAmbient(const Color& ambient)
{
	this->ambient = ambient;
}

void Light::SetDiffuse(const Color& diffuse)
{
	this->diffuse = diffuse;
}

void Light::SetSpecular(const Color& specular)
{
	this->specular = specular;
}
