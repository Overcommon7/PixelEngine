#include "pch.h"
#include "Commands.h"
#include "Utilities.h"
#include "MatrixStack.h"

class POPMATRIX : public Commands
{
public:
    POPMATRIX() {}
    //Returns The Name Of The Function
    string GetName() const override { return "PopMatrix"; }

    //Invoke Gets Called When A PixelScript Calls The Name Of The Fuction
    void Invoke(const vector<string>& params) const override
    {
        MatrixStack::PopMatrix();
    }
};