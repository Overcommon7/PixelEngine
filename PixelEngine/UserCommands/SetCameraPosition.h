#include "pch.h"
#include "Commands.h"
#include "Utilities.h"
#include "Camera.h"

class SETCAMERAPOSITION : public Commands
{
public:
    SETCAMERAPOSITION() {}
    //Returns The Name Of The Function
    string GetName() const override { return "SetCameraPosition"; }

    //Invoke Gets Called When A PixelScript Calls The Name Of The Fuction
    void Invoke(const vector<string>& params) const override
    {
        if (params.size() < 3) return;
        Math::Vector3 vec = {};
        if (!Utils::TryParse(params[0], vec.x)) return;
        if (!Utils::TryParse(params[1], vec.y)) return;
        if (!Utils::TryParse(params[2], vec.z)) return;
        PixelCamera::SetPosition(vec);
    }
};