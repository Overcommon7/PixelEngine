#include "pch.h"
#include "LightManager.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "Utilities.h"

void LightManager::OnNewFrame()
{
	mLights.clear();
}

void LightManager::AddDirectionalLight(const Math::Vector3& direction)
{
	auto light = make_unique<DirectionalLight>();
	light->SetDirection(direction);
	light->SetAmbient(mAmbient);
	light->SetDiffuse(mDiffuse);
	light->SetSpecular(mSpecular);
	mLights.emplace_back(std::move(light));
}

void LightManager::AddPointLight(const Math::Vector3& position, const Math::Vector3 attenuation)
{
	auto light = make_unique<PointLight>();
	light->SetAmbient(mAmbient);
	light->SetDiffuse(mDiffuse);
	light->SetSpecular(mSpecular);
	light->SetPosition(position);
	light->SetAttenuation(attenuation.x, attenuation.y, attenuation.z);
	mLights.emplace_back(std::move(light));
}

void LightManager::SetLightingAmbient(const Color& ambient)
{
	mAmbient = ambient;
}

void LightManager::SetLightingDiffuse(const Color& diffuse)
{
	mDiffuse = diffuse;
}

void LightManager::SetLightingSpecular(const Color& specular)
{
	mSpecular = specular;
}

Color LightManager::ComputeLightColor(const Math::Vector3& position, const Math::Vector3& normal)
{
	if (mLights.empty()) return WHITE;

	Color color = { 0, 0, 0, 255 };
	for (auto& light : mLights)
		color = Utils::AddColor(color, light->ComputeLightColor(position, normal));

	return color;
}
