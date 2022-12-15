#include "pch.h"
#include "Commands.h"
#include "PrimitiveManager.h"
#include "Utilities.h"

class ENDDRAW : public Commands
{
public:
    ENDDRAW() {}
    //Returns The Name Of The Function
    string GetName() const override { return "EndDraw"; }

    //Invoke Gets Called When A PixelScript Calls The Name Of The Fuction
    void Invoke(const vector<string>& params) const override
    {
        if (params.empty() || Utils::ToLowerString(params.front()) != "true") PrimitiveManager::EndDraw();
        else PrimitiveManager::EndDraw(true);        
    }
};