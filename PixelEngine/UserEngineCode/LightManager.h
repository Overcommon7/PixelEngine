#pragma once
#include "Light.h"
#include "Vector3.h"

class LightManager
{
    LightManager() = delete;
    LightManager(const LightManager& l) = delete;
    LightManager& operator=(const LightManager& l) = delete;

public:
    
    static void OnNewFrame();
    static void AddDirectionalLight(const Math::Vector3& direction);
    static void AddPointLight(const Math::Vector3& position, const Math::Vector3 attenuation = { 1.f, 0.f, 0.f });

    static void SetLightingAmbient(const Color& ambient);
    static void SetLightingDiffuse(const Color& diffuse);
    static void SetLightingSpecular(const Color& specular);

    static Color ComputeLightColor(const Math::Vector3& position, const Math::Vector3& normal);

private:

    inline static vector<unique_ptr<Light>> mLights = {};
    inline static Color mAmbient = WHITE;
    inline static Color mDiffuse = WHITE;
    inline static Color mSpecular = WHITE;
};

