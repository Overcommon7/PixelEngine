#include "pch.h"
#include "DirectionalLight.h"
#include "Camera.h"
#include "MaterialManager.h"
#include "Utilities.h"

Math::Color DirectionalLight::ComputeLightColor(const Math::Vector3& pos, const Math::Vector3& normal) const
{	
	Math::Color colorAmbient = Utils::MultiplyColor(ambient, MaterialManager::GetMaterialAmbient());

	auto dirToLight = direction * -1;
	float dot = dirToLight.DotProduct(normal);
	Math::Color colorDiffuse = diffuse * MaterialManager::GetMaterialDiffuse() * std::max(dot, 0.0f);

	auto dirToEye = PixelCamera::GetPosition();
	auto half = (dirToLight + dirToEye).Normalize();
	float falloff = pow(half.DotProduct(normal), MaterialManager::GetMaterialShininess());
	Math::Color colorSpecular = specular * MaterialManager::GetMaterialSpecular() * std::max(falloff, 0.0f);
	Math::Color value = colorAmbient + colorDiffuse + colorSpecular;
	return value;
}

void DirectionalLight::SetDirection(const Vector3& dir)
{
	direction = dir;
}
