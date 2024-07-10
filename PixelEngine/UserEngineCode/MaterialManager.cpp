#include "pch.h"
#include "MaterialManager.h"

void MaterialManager::OnNewFrame()
{
	mAmbient =  WHITE;
	mDiffuse =  WHITE;
	mSpecular = WHITE;
	mShininess = 1.0f;
}

void MaterialManager::SetMaterialAmbient(Math::Color ambient)
{
	mAmbient = ambient;
}

void MaterialManager::SetMaterialDiffuse(Math::Color diffuse)
{
	mDiffuse = diffuse;
}

void MaterialManager::SetMaterialSpecular(Math::Color specular)
{
	mSpecular = specular;
}

void MaterialManager::SetMaterialShininess(float shininess)
{
	mShininess = shininess;
}

Math::Color MaterialManager::GetMaterialAmbient()
{
	return mAmbient;
}

Math::Color MaterialManager::GetMaterialDiffuse()
{
	return mDiffuse;
}

Math::Color MaterialManager::GetMaterialSpecular()
{
	return mSpecular;
}

float MaterialManager::GetMaterialShininess()
{
	return mShininess;
}
