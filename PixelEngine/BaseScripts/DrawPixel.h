#include "pch.h"
#include "Commands.h"
#include "Draw.h"
#include "Defines.h"

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
        int x = stoi(params[0]), y = stoi(params[1]);
        if (x < 0 || x > screenWidth / Draw::GetPixelSize()) return;
        if (y < 0 || y > screenHeight / Draw::GetPixelSize()) return;
        Draw::DrawScaledPixel(x, y);
    }
};