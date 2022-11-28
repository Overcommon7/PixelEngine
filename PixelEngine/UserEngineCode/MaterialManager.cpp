#include "pch.h"
#include "MaterialManager.h"

void MaterialManager::OnNewFrame()
{
	mAmbient =  WHITE;
	mDiffuse =  WHITE;
	mSpecular = WHITE;
	mShininess = 1.0f;
}

void MaterialManager::SetMaterialAmbient(Color ambient)
{
	mAmbient = ambient;
}

void MaterialManager::SetMaterialDiffuse(Color diffuse)
{
	mDiffuse = diffuse;
}

void MaterialManager::SetMaterialSpecular(Color specular)
{
	mSpecular = specular;
}

void MaterialManager::SetMaterialShininess(float shininess)
{
	mShininess = shininess;
}

Color MaterialManager::GetMaterialAmbient()
{
	return mAmbient;
}

Color MaterialManager::GetMaterialDiffuse()
{
	return mDiffuse;
}

Color MaterialManager::GetMaterialSpecular()
{
	return mSpecular;
}

float MaterialManager::GetMaterialShininess()
{
	return mShininess;
}
