#pragma once
#include "Light.h"

class DirectionalLight :
    public Light
{
public:
    Color ComputeLightColor(const Math::Vector3& pos, const Math::Vector3& normal) const override;
    void SetDirection(const Vector3& dir);
protected:
    Math::Vector3 direction;
};

