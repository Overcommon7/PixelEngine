#include "pch.h"
#include "Commands.h"
#include "Draw.h"

class ToggleGrid : public Commands
{
public:
    ToggleGrid() {}
    //Returns The Name Of The Function
    string GetName() override { return "ToggleGrid"; }

    //Invoke Gets Called When A PixelScript Calls The Name Of The Fuction
    void Invoke(const vector<string>& params) override
    {
        if (params.empty())
            Draw::ToggleGrid();
        else Draw::SetGrid(params[0] == "true");
    }
};