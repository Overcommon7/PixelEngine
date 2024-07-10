#include "pch.h"
#include "PointLight.h"
#include "Camera.h"
#include "MaterialManager.h"


Math::Color PointLight::ComputeLightColor(const Math::Vector3& position, const Math::Vector3& normal) const
{
	auto dirToLight = mPosition - position;
	auto distanceToLight = dirToLight.Magnitude();
	dirToLight = dirToLight / distanceToLight;

	float atten = 1.0f / (mAttenConst + (mAttenLinear * distanceToLight) + (mAttenQuadratic * distanceToLight * distanceToLight));
	float attenValue = std::clamp(atten, 0.0f, 1.0f);

	Math::Color colorAmbient = ambient * MaterialManager::GetMaterialAmbient() * attenValue;

	float dot = dirToLight.DotProduct(normal);
	Math::Color colorDiffuse = diffuse * MaterialManager::GetMaterialDiffuse() * std::max(dot, 0.0f) * attenValue;

	auto dirToEye = PixelCamera::GetPosition();
	auto half = (dirToLight + dirToEye).Normalize();
	float falloff = pow(half.DotProduct(normal), MaterialManager::GetMaterialShininess());
	Math::Color colorSpecular = specular * MaterialManager::GetMaterialSpecular() * std::max(falloff, 0.0f) * attenValue;

	return colorAmbient + colorDiffuse + colorSpecular;
}

void PointLight::SetPosition(const Vector3& position)
{
	mPosition = position;
}

void PointLight::SetAttenuation(float constant, float linear, float quadratic)
{
	mAttenConst = constant;
	mAttenLinear = linear;
	mAttenQuadratic = quadratic;
}
