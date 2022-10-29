#include "pch.h"
#include "Commands.h"
#include "PrimitiveManager.h"
#include "Utilities.h"

class BEGINDRAW : public Commands
{
public:
    BEGINDRAW() {}
    //Returns The Name Of The Function
    string GetName() const override { return "BeginDraw"; }

    //Invoke Gets Called When A PixelScript Calls The Name Of The Fuction
    void Invoke(const vector<string>& params) const override
    {
        if (params.empty()) return;
        string temp = Utils::ToLowerString(params.front());
        Topolgy type = Topolgy::Point;
        if (temp == "line") type = Topolgy::Line;
        else if (temp == "triangle") type = Topolgy::Triangle;        
        PrimitiveManager::BeginDraw(type);
    }
};