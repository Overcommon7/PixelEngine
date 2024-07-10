#include "pch.h"
#include "Commands.h"
#include "Rasterizer.h"
#include "Utilities.h"

class SETFILLMODE : public Commands
{
public:
    SETFILLMODE() {}
    //Returns The Name Of The Function
    string GetName() const override { return "SetFillMode"; }

    //Invoke Gets Called When A PixelScript Calls The Name Of The Fuction
    void Invoke(const vector<string>& params) const override
    {
        if (params.empty()) return;
        string str = Utils::ToLowerString(params.front());
        if (str == "wireframe") Rasterizer::SetFillMode(FillMode::Wireframe);
        else Rasterizer::SetFillMode(FillMode::Solid);
        
    }
};