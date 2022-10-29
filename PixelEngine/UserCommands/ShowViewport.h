#include "pch.h"
#include "Commands.h"
#include "Utilities.h"
#include "Clipper.h"

class SHOWVIEWPORT : public Commands
{
public:
    SHOWVIEWPORT() {}
    //Returns The Name Of The Function
    string GetName() const override { return "ShowViewport"; }

    //Invoke Gets Called When A PixelScript Calls The Name Of The Fuction
    void Invoke(const vector<string>& params) const override
    {
        if (params.empty()) return;
        if (Utils::ToLowerString(params.front()) == "true") Clipper::ShowViewport(true);
        else Clipper::ShowViewport(false);
        if (params.size() == 2) Clipper::SetViewportColor(Utils::StringToColor(params[1]));
    }
};