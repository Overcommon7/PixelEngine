#include "pch.h"
#include "Commands.h"
#include "Utilities.h"
#include "LightManager.h"

class ADDDIRECTIONALLIGHT : public Commands
{
public:
    ADDDIRECTIONALLIGHT() {}
    //Returns The Name Of The Function
    string GetName() const override { return "AddDirectionalLight"; }

    //Invoke Gets Called When A PixelScript Calls The Name Of The Fuction
    void Invoke(const vector<string>& params) const override
    {
        if (params.size() < 3) return;
        vector<float> values;
        if (!Utils::TryParse(params, values)) return;
        LightManager::AddDirectionalLight(values);
    }
};
