#include "pch.h"
#include "Commands.h"
#include "Pixel.h"

class DRAWPIXEL : public Commands
{
public:
    DRAWPIXEL() {}
    //Returns The Name Of The Function
    string GetName() override { return "DrawPixel"; }

    //Invoke Gets Called When A PixelScript Calls The Name Of The Fuction
    void Invoke(const vector<string>& params) override
    {
        if (params.size() < 2) return;
        Pixel::DrawPixel(stoi(params[0]), stoi(params[1]));
    }
};