#include "pch.h"
#include "Commands.h"
#include "Rasterizer.h"
#include "Utilities.h"

class CHANGECOLOR : public Commands
{
public:
    CHANGECOLOR() {}
    //Returns The Name Of The Function
    string GetName() const override { return "ChangeColor"; }

    //Invoke Gets Called When A PixelScript Calls The Name Of The Fuction
    void Invoke(const vector<string>& params) const override
    {
        if (params.size() == 1)
            Rasterizer::SetPixelColor(Utils::StringToColor(params.front()));
        if (params.size() == 4)
            Rasterizer::SetPixelColor(stoi(params[0]), stoi(params[1]), stoi(params[2]), stoi(params[3]));
        else if (params.size() == 3)
            Rasterizer::SetPixelColor(stoi(params[0]), stoi(params[1]), stoi(params[2]));
    }
};