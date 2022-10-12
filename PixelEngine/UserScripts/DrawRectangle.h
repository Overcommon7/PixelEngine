#include "pch.h"
#include "Commands.h"
#include "Pixel.h"
#include "Utilities.h"

class DRAWRECTANGLE : public Commands
{
public:
    DRAWRECTANGLE() {}
    //Returns The Name Of The Function
    string GetName() override { return "DrawRectangle"; }

    //Invoke Gets Called When A PixelScript Calls The Name Of The Fuction
    void Invoke(const vector<string>& params) override
    {
        if (params.size() < 3) return;
        Color temp = Pixel::GetPixelColor();
        int posX = stoi(params[0]);
        int posY = stoi(params[1]);
        if (!Utils::IsFloat(params[2])) return;
        short size = stoi(params[2]);

        bool hollow = false;
        if (params.size() >= 4)
            hollow = params[3] == "true";
        if (params.size() == 5)
            Pixel::SetPixelColor(Utils::StringToColor(params[4]));
        for (short i = 0; i < size; i++)
        {
            for (short j = 0; j < size; j++)
            {
                if (!hollow || (hollow && (j == 0 || j == size - 1) || (i == 0 || i == size - 1)))
                    Pixel::DrawPixel(posX + i, posY + j);
            }
        }
        Pixel::SetPixelColor(temp);
    }
};