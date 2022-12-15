#include "pch.h"
#include "Commands.h"
#include "Rasterizer.h"
#include "Utilities.h"

class CHANGEPIXELCOLOR : public Commands
{
public:
    CHANGEPIXELCOLOR() {}
    //Returns The Name Of The Function
    string GetName() const override { return "ChangePixelColor"; }

    //Invoke Gets Called When A PixelScript Calls The Name Of The Fuction
    void Invoke(const vector<string>& params) const override
    {
       
        if (params.size() == 1)
        {
            Rasterizer::SetPixelColor(Utils::StringToColor(params.front()));
            return;
        }           
        vector<int> ints(params.size(), 0);
        for (short i = 0; i < params.size(); i++)
            if (!Utils::TryParse(params[i], ints[i])) return;

        if (params.size() == 4)
            Rasterizer::SetPixelColor(ints[0], ints[1], ints[2], ints[3]);
        else if (params.size() == 3)
            Rasterizer::SetPixelColor(ints[0], ints[1], ints[2]);
    }
};
