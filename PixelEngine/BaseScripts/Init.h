#include "pch.h"
#include "Commands.h"
#include "Defines.h"

class Init : public Commands
{
public:
    Init() {}
    //Returns The Name Of The Function
    string GetName() const override { return "Init"; }

    //Invoke Gets Called When A PixelScript Calls The Name Of The Fuction
    void Invoke(const vector<string>& params) const override
    {
        if (params.size() < 3) return;
        Draw::Initalize(stoi(params[0]), stoi(params[1]), stoi(params[2]));
    }
};