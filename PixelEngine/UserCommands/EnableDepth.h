#include "Commands.h"
#include "Utilities.h"
#include "DepthBuffer.h"

class ENABLEDEPTH : public Commands
{
public:
    ENABLEDEPTH() {}
    //Returns The Name Of The Function
    string GetName() const override { return "EnableDepth"; }

    //Invoke Gets Called When A PixelScript Calls The Name Of The Fuction
    void Invoke(const vector<string>& params) const override
    {
        if (params.empty()) return;
        if (Utils::ToLowerString(params.front()) == "true") DepthBuffer::SetEnabled(true);
        else DepthBuffer::SetEnabled(false);
    }
};