#include "pch.h"
#include "Commands.h"
#include "Pixel.h"
#include "Utilities.h"

class DRAWLINE : public Commands
{
public:
    DRAWLINE() {}
    //Returns The Name Of The Function
    string GetName() override { return "DrawLine"; }

    void PlotLineHigh(const Vector2& start, const Vector2& end)
    {
        float dx = end.x - start.x;
        float dy = end.y - start.y;
        float xi = 1;

        if (dx < 0)
        {

            xi = -1;
            dx = -dx;
        }
        float D = (2 * dx) - dy;
        float x = start.x;

        for (float y = start.y; y <= end.y; y++)
        {
            Pixel::DrawPixel((int)x, (int)y);
            if (D > 0)
            {
                x = x + xi;
                D = D + (2 * (dx - dy));
            }
            else D = D + 2 * dx;
        }
    }
    void PlotLineLow(const Vector2& start, const Vector2& end)
    {
        float dx = end.x - start.x;
        float dy = end.y - start.y;
        float yi = 1;

        if (dy < 0)
        {

            yi = -1;
            dy = -dy;
        }
        float D = (2 * dy) - dx;
        float y = start.y;

        for (float x = start.x; x <= end.x; x++)
        {
            Pixel::DrawPixel((int)x, (int)y);
            if (D > 0)
            {
                y = y + yi;
                D = D + (2 * (dy - dx));
            }
            else D = D + 2 * dy;
        }
    }
    //Invoke Gets Called When A PixelScript Calls The Name Of The Fuction
    void Invoke(const vector<string>& params) override
    {
        if (params.size() < 4) return;
        Vector2 start = { stof(params[0]), stof(params[1]) };
        Vector2 end = { stof(params[2]), stof(params[3]) };
        if (abs(end.y - start.y) < abs(end.x - start.x))
        {
            if (start.x > end.x) PlotLineLow(end, start);
            else PlotLineLow(start, end);
        }
        else
        {
            if (start.y > end.y) PlotLineHigh(end, start);
            else PlotLineHigh(start, end);
        }
    }
};