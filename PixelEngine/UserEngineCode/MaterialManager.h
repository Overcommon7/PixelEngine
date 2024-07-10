#pragma once


class MaterialManager
{

	inline static Math::Color mAmbient =  WHITE;
	inline static Math::Color mDiffuse =  WHITE;
	inline static Math::Color mSpecular = WHITE;
	inline static float mShininess = 1.0f;

public:

	MaterialManager() = delete;
	MaterialManager(const MaterialManager& m) = delete;
	MaterialManager& operator=(const MaterialManager& m) = delete;

	static void OnNewFrame();

	static void SetMaterialAmbient(Math::Color ambient);
	static void SetMaterialDiffuse(Math::Color diffuse);
	static void SetMaterialSpecular(Math::Color specular);
	static void SetMaterialShininess(float shininess);

	static Math::Color GetMaterialAmbient();
	static Math::Color GetMaterialDiffuse();
	static Math::Color GetMaterialSpecular();
	static float GetMaterialShininess();
};

