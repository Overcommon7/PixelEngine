#include "pch.h"
#include "Commands.h"
#include "Utilities.h"
#include "Camera.h"

class SETFARPLANE : public Commands
{
public:
    SETFARPLANE() {}
    //Returns The Name Of The Function
    string GetName() const override { return "SetFarPlane"; }

    //Invoke Gets Called When A PixelScript Calls The Name Of The Fuction
    void Invoke(const vector<string>& params) const override
    {
        if (params.empty()) return;
        float pos = 0;
        if (!Utils::TryParse(params.front(), pos)) return;
        PixelCamera::SetFarPlane(pos);
    }
};