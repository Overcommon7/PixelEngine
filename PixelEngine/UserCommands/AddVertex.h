#pragma once
#include "pch.h"
#include "Commands.h"
#include "Utilities.h"
#include "PrimitiveManager.h"
#include "Draw.h"

class ADDVERTEX : public Commands
{
public:
    ADDVERTEX() {}
    //Returns The Name Of The Function
    string GetName() const override { return "AddVertex"; }

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

            if (f[2] > 1.01f && f[3] > 1.01f && f[4] > 1.01f) v = Vertex({ f.front(), f[1] }, Color(f[2], f[3], f[4], 255));
            else v = Vertex({ f.front(), f[1] }, Utils::UnitTo8BitColor(f[2], f[3], f[4]));
            break;
        case 6:
            for (short i = 0; i < params.size(); i++)
                if (!Utils::TryParse(params[i], f[i])) return;

            if (f[3] > 1.01f && f[4] > 1.01f && f[5] > 1.01f) v = Vertex({ f[0], f[1], f[2] }, Color(f[3], f[4], f[5], 255));
            else 
                v = Vertex({ f[0], f[1], f[2] }, Utils::UnitTo8BitColor(f[3], f[4], f[5]));
            break;
        default:
            return;
            break;
        }
        v = v;
        PrimitiveManager::AddVertex(v);
    }
};
