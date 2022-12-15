#pragma once
#include "pch.h"
#include "Commands.h"
#include "Utilities.h"
#include "LightManager.h"

class ADDPOINTLIGHT : public Commands
{
public:
    ADDPOINTLIGHT() {}
    //Returns The Name Of The Function
    string GetName() const override { return "AddPointLight"; }

    //Invoke Gets Called When A PixelScript Calls The Name Of The Fuction
    void Invoke(const vector<string>& params) const override
    {
        if (params.size() < 3) return;
        vector<float> values;
        if (!Utils::TryParse(params, values)) return;
        if (params.size() > 5)  LightManager::AddPointLight({ values[0], values[1], values[2] }, { values[3], values[4], values[5] });
        else LightManager::AddPointLight({ values[0], values[1], values[2] });
    }
};