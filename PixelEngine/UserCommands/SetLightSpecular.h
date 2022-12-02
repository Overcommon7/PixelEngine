#include "pch.h"
#include "Commands.h"
#include "Utilities.h"
#include "LightManager.h"

class SETLIGHTSPECULAR : public Commands
{
public:
    SETLIGHTSPECULAR() {}
    //Returns The Name Of The Function
    string GetName() const override { return "SetLightSpecular"; }

    //Invoke Gets Called When A PixelScript Calls The Name Of The Fuction
    void Invoke(const vector<string>& params) const override
    {
        if (params.size() < 3) return;
        vector<float> values;
        if (!Utils::TryParse(params, values)) return;
        Math::Color c;
        if (values[0] > 1 && values[1] > 1 && values[2] > 1) c = Math::Color(values[0], values[1], values[2], 255);
        else c = Utils::UnitTo8BitColor(values[0], values[1], values[2]);
        LightManager::SetLightingSpecular(c);
    }
};