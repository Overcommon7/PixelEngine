#include "pch.h"
#include "DirectionalLight.h"
#include "Camera.h"
#include "MaterialManager.h"
#include "Utilities.h"

Color DirectionalLight::ComputeLightColor(const Math::Vector3& pos, const Math::Vector3& normal) const
{	
	Color colorAmbient = Utils::MultiplyColor(ambient, MaterialManager::GetMaterialAmbient());

	auto dirToLight = direction * -1;
	float dot = dirToLight.DotProduct(normal);
	Color colorDiffuse = Utils::MultiplyColor(Utils::MultiplyColor(diffuse, MaterialManager::GetMaterialDiffuse()), std::max(dot, 0.0f));

	auto dirToEye = PixelCamera::GetPosition();
	auto half = (dirToLight + dirToEye).Normalize();
	float falloff = pow(half.DotProduct(normal), MaterialManager::GetMaterialShininess());
	Color colorSpecular = Utils::MultiplyColor(Utils::MultiplyColor(specular, MaterialManager::GetMaterialSpecular()), std::max(falloff, 0.0f));

	return Utils::AddColor(Utils::AddColor(colorAmbient, colorDiffuse), colorSpecular);
}

void DirectionalLight::SetDirection(const Vector3& dir)
{
	direction = dir;
}
