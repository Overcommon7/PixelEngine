#include "pch.h"
#include "Commands.h"
#include "Utilities.h"

class SETVIEWPORT : public Commands
{
public:
    SETVIEWPORT() {}
    //Returns The Name Of The Function
    string GetName() const override { return "SetViewport"; }

    //Invoke Gets Called When A PixelScript Calls The Name Of The Fuction
    void Invoke(const vector<string>& params) const override
    {
        if (params.size() < 4) return;
        Rectangle vp = {};
        if (!Utils::TryParse(params[0], vp.x)) return;
        if (!Utils::TryParse(params[1], vp.y)) return;
        if (!Utils::TryParse(params[2], vp.width)) return;
        if (!Utils::TryParse(params[3], vp.height)) return;
        
        Clipper::SetViewport(vp);
    }
};