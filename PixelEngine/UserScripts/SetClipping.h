#include "pch.h"
#include "Commands.h"
#include "Utilities.h"
#include "Clipper.h"

class SETCLIPPING : public Commands
{
public:
    SETCLIPPING() {}
    //Returns The Name Of The Function
    string GetName() const override { return "SetClipping"; }

    //Invoke Gets Called When A PixelScript Calls The Name Of The Fuction
    void Invoke(const vector<string>& params) const override
    {
        if (params.empty()) return;
        if (Utils::ToLowerString(params.front()) == "true")  Clipper::SetClipping(true);
        else Clipper::SetClipping(false);
    }
};