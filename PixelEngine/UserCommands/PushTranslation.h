#include "pch.h"
#include "Commands.h"
#include "Utilities.h"

class PUSHTRANSLATION : public Commands
{
public:
    PUSHTRANSLATION() {}
    //Returns The Name Of The Function
    string GetName() const override { return "PushTranslation"; }

    //Invoke Gets Called When A PixelScript Calls The Name Of The Fuction
    void Invoke(const vector<string>& params) const override
    {
        if (params.size() < 3) return;
        vector<float> results(3, 0);
        for (short i = 0; i < 3; i++)
            if (!Utils::TryParse(params[i], results[i])) return;
        MatrixStack::PushTranslation(Vector3(results[0], results[1], results[2]));
    }
};