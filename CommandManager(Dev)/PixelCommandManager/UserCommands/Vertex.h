#include "pch.h"
#include "Commands.h"
#include "Utilities.h"
#include "PrimitiveManager.h"
#include "Draw.h"

class VERTEX : public Commands
{
public:
    VERTEX() {}
    //Returns The Name Of The Function
    string GetName() const override { return "Vertex"; }

    //Invoke Gets Called When A PixelScript Calls The Name Of The Fuction
    void Invoke(const vector<string>& params) const override
    {
        Vertex v = {};
        vector<float> f(params.size(), 0);
        switch (params.size())
        {
        case 2:
            for (short i = 0; i < params.size(); i++)
                if (!Utils::TryParse(params[i], f[i])) return;
            v = Vertex({ f.front(), f.back() }, Draw::GetPixelColor());
            break;
        case 3:
            for (short i = 0; i < 2; i++)
                if (!Utils::TryParse(params[i], f[i])) return;
            if (Utils::TryParse(params.back(), f.back())) v = Vertex({ f.front(), f[1], f.back() }, Draw::GetPixelColor());
            else v = Vertex({ f.front(), f[1] }, Utils::StringToColor(params.back()));
            break;
        case 4:
            for (short i = 0; i < 3; i++)
                if (!Utils::TryParse(params[i], f[i])) return;
            v = Vertex({ f.front(), f[1], f.back() }, Utils::StringToColor(params.back()));
            break;
        case 5:
            for (short i = 0; i < params.size(); i++)
                if (!Utils::TryParse(params[i], f[i])) return;
            v = Vertex({ f.front(), f[1]}, Color(f[2], f[3], f.back(), 255));
            break;
        case 6:
            for (short i = 0; i < params.size(); i++)
            {
                for (short i = 0; i < params.size(); i++)
                    if (!Utils::TryParse(params[i], f[i])) return;
            }
            v = Vertex({ f.front(), f[1], f[2] }, Color(f[3], f[4], f.back(), 255));
            break;
        default:
            return;
            break;
        }        
        PrimitiveManager::AddVertex(v);
    }
};
