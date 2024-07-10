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

    static void SetLightingAmbient(const Math::Color& ambient);
    static void SetLightingDiffuse(const Math::Color& diffuse);
    static void SetLightingSpecular(const Math::Color& specular);

    static Math::Color ComputeLightColor(const Math::Vector3& position, const Math::Vector3& normal);

private:

    inline static vector<unique_ptr<Light>> mLights = {};
    inline static Math::Color mAmbient = WHITE;
    inline static Math::Color mDiffuse = WHITE;
    inline static Math::Color mSpecular = WHITE;
};

