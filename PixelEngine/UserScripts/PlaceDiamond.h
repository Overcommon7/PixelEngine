#include "pch.h"
#include "Commands.h"
#include "Pixel.h"

class PlaceDiamond : public Commands
{
public:
    PlaceDiamond() {}
    //Returns The Name Of The Function
    string GetName() override { return "PlaceDiamond"; }

    //Invoke Gets Called When A PixelScript Calls The Name Of The Fuction
    void Invoke(const vector<string>& params) override
    {

    }
};