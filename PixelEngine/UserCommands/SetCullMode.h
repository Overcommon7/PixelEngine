#include "Commands.h"
#include "PrimitiveManager.h"
#include "Utilities.h"

class SETCULLMODE : public Commands
{
public:
    SETCULLMODE() {}
    //Returns The Name Of The Function
    string GetName() const override { return "SetCullMode"; }

    //Invoke Gets Called When A PixelScript Calls The Name Of The Fuction
    void Invoke(const vector<string>& params) const override
    {
        if (params.empty()) return;
        if (Utils::ToLowerString(params.front()) == "back") PrimitiveManager::SetCullmode(Cullmode::Back);
        else if (Utils::ToLowerString(params.front()) == "front") PrimitiveManager::SetCullmode(Cullmode::Front);
        else PrimitiveManager::SetCullmode(Cullmode::None);
    }
};