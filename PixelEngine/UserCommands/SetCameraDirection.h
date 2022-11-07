#include "pch.h"
#include "Commands.h"
#include "Utilities.h"

class SETCAMERADIRECTION : public Commands
{
public:
    SETCAMERADIRECTION() {}
    //Returns The Name Of The Function
    string GetName() const override { return "SetCameraDirection"; }

    //Invoke Gets Called When A PixelScript Calls The Name Of The Fuction
    void Invoke(const vector<string>& params) const override
    {

    }
};