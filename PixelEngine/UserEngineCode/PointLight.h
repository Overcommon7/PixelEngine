#pragma once
#include "Light.h"
#include "Vector3.h"

class PointLight :
    public Light
{
public:
    virtual Color ComputeLightColor(const Math::Vector3& position, const Math::Vector3& normal) const override;

    void SetPosition(const Vector3& position);
    void SetAttenuation(float constant, float linear, float quadratic);

protected:

    Math::Vector3 mPosition;
    float mAttenConst = -1.f;
    float mAttenLinear = -1.f;
    float mAttenQuadratic = -1.f;
};

