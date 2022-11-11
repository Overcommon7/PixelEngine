#include "pch.h"
#include "Commands.h"
#include "Utilities.h"
#include "Camera.h"

class SETFOV : public Commands
{
public:
    SETFOV() {}
    //Returns The Name Of The Function
    string GetName() const override { return "SetFOV"; }

    //Invoke Gets Called When A PixelScript Calls The Name Of The Fuction
    void Invoke(const vector<string>& params) const override
    {
        if (params.empty()) return;
        float fov = 0;
        if (!Utils::TryParse(params.front(), fov)) return;
        PixelCamera::SetFOV(fov);
    }
};