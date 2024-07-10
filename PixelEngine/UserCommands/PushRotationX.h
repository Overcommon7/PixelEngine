#include "pch.h"
#include "Commands.h"
#include "Utilities.h"
#include "MatrixStack.h"

class PUSHROTATIONX : public Commands
{
public:
    PUSHROTATIONX() {}
    //Returns The Name Of The Function
    string GetName() const override { return "PushRotationX"; }

    //Invoke Gets Called When A PixelScript Calls The Name Of The Fuction
    void Invoke(const vector<string>& params) const override
    {
        if (params.empty()) return;
        float result = 0;
        if (!Utils::TryParse(params.front(), result)) return;
        MatrixStack::PushRotationX(result * DEG2RAD);
    }
};