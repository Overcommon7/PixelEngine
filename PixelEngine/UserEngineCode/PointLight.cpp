#include "pch.h"
#include "PointLight.h"
#include "Camera.h"
#include "MaterialManager.h"


Color PointLight::ComputeLightColor(const Math::Vector3& position, const Math::Vector3& normal) const
{
	auto dirToLight = mPosition - position;
	auto distanceToLight = dirToLight.Magnitude();
	dirToLight = dirToLight / distanceToLight;

	float atten = 1.0f / (mAttenConst + (mAttenLinear * distanceToLight) + (mAttenQuadratic * distanceToLight * distanceToLight));
	float attenValue = std::clamp(atten, 0.0f, 1.0f);

	Color colorAmbient = Utils::MultiplyColor(Utils::MultiplyColor(ambient, MaterialManager::GetMaterialAmbient()), attenValue);

	float dot = dirToLight.DotProduct(normal);
	Color colorDiffuse = 
			Utils::MultiplyColor(
			Utils::MultiplyColor(
			Utils::MultiplyColor(diffuse, MaterialManager::GetMaterialDiffuse()),
			std::max(dot, 0.0f)),
			attenValue);

	auto dirToEye = PixelCamera::GetPosition();
	auto half = (dirToLight + dirToEye).Normalize();
	float falloff = pow(half.DotProduct(normal), MaterialManager::GetMaterialShininess());
	Color colorSpecular = 
		Utils::MultiplyColor(
		Utils::MultiplyColor(
		Utils::MultiplyColor(specular, MaterialManager::GetMaterialSpecular()), 
		std::max(falloff, 0.0f)), 
		attenValue);

	return Utils::AddColor(Utils::AddColor(colorAmbient, colorDiffuse), colorSpecular);
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
