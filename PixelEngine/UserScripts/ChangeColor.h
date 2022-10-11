#include "pch.h"
#include "Commands.h"
#include "Pixel.h"
#include "Utilities.h"

class ChangeColor : public Commands
{
public:
    ChangeColor() {}
    //Returns The Name Of The Function
    string GetName() override { return "ChangeColor"; }

    //Invoke Gets Called When A PixelScript Calls The Name Of The Fuction
    void Invoke(const vector<string>& params) override
    {
        if (params.size() == 1)
            Pixel::SetPixelColor(Utils::StringToColor(params.front()));
        if (params.size() == 4)
            Pixel::SetPixelColor(stoi(params[0]), stoi(params[1]), stoi(params[2]), stoi(params[3]));
        else if (params.size() == 3)
            Pixel::SetPixelColor(stoi(params[0]), stoi(params[1]), stoi(params[2]));
    }
};