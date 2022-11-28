#pragma once
class MaterialManager
{

	inline static Color mAmbient =  WHITE;
	inline static Color mDiffuse =  WHITE;
	inline static Color mSpecular = WHITE;
	inline static float mShininess = 1.0f;

public:

	MaterialManager() = delete;
	MaterialManager(const MaterialManager& m) = delete;
	MaterialManager& operator=(const MaterialManager& m) = delete;

	static void OnNewFrame();

	static void SetMaterialAmbient(Color ambient);
	static void SetMaterialDiffuse(Color diffuse);
	static void SetMaterialSpecular(Color specular);
	static void SetMaterialShininess(float shininess);

	static Color GetMaterialAmbient();
	static Color GetMaterialDiffuse();
	static Color GetMaterialSpecular();
	static float GetMaterialShininess();
};

