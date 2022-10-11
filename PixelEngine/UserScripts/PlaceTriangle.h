#include "pch.h"
#include "Commands.h"
#include "Pixel.h"
#include "Utilities.h"

class PlaceTriangle : public Commands
{
public:
    PlaceTriangle() {}
    //Returns The Name Of The Function
    string GetName() override { return "PlaceTriangle"; }

    //Invoke Gets Called When A PixelScript Calls The Name Of The Fuction
    void Invoke(const vector<string>& params) override
    {
        if (params.size() < 3) return;
        Color temp = Pixel::GetPixelColor();
        short height = stoi(params[2]);
        int posX = stoi(params[0]) + height - 1;
        int posY = stoi(params[1]) - 1;
        short offset = 0;
        if (params.size() >= 4)
            Pixel::SetPixelColor(Utils::StringToColor(params[3]));

        for (short i = 1, k = 0; i <= height; ++i, k = 0)
        {
            while (k != 2 * i - 1)
            {
                Pixel::DrawPixel(k + posX - offset, i + posY);
                ++k;
            }
            ++offset;
        }
        Pixel::SetPixelColor(temp);
    }
};