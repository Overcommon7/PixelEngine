#include "pch.h"
#include "Commands.h"
#include "Draw.h"
#include "Defines.h"
#include "Utilities.h"

class DRAWPIXEL : public Commands
{
public:
    DRAWPIXEL() {}
    //Returns The Name Of The Function
    string GetName() const override { return "DrawPixel"; }

    //Invoke Gets Called When A PixelScript Calls The Name Of The Fuction
    void Invoke(const vector<string>& params) const override
    {
        if (params.size() < 2) return;
        float x, y ;
        if (!Utils::TryParse(params.front(), x)) return;
        if (!Utils::TryParse(params.back(), y)) return;
        if (x < 0 || x > screenWidth / Draw::GetPixelSize()) return;
        if (y < 0 || y > screenHeight / Draw::GetPixelSize()) return;
        Draw::DrawScaledPixel(x, y);
    }
};