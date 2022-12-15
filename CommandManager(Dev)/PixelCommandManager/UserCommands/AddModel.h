#include "pch.h"
#include "Commands.h"
#include "Utilities.h"

class ADDMODEL : public Commands
{
public:
    ADDMODEL() {}
    //Returns The Name Of The Function
    string GetName() const override { return "AddModel"; }

    //Invoke Gets Called When A PixelScript Calls The Name Of The Fuction
    void Invoke(const vector<string>& params) const override
    {

    }
};