#include "pch.h"
#include "Rasterizer.h"
#include "Defines.h"
#include "Draw.h"
#include "Utilities.h"

void Rasterizer::PlotLineHigh(const Vertex& start, const Vertex& end)
{
    float dx = end.pos.x - start.pos.x;
    float dy = end.pos.y - start.pos.y;
    float xi = 1;

    if (dx < 0)
    {

        xi = -1;
        dx = -dx;
    }
    float D = (2 * dx) - dy;
    float x = start.pos.x;

    for (float y = start.pos.y; y <= end.pos.y; y++)
    {
        Rasterizer::DrawPixel(Vertex(Math::Vector3(x, y, 0), Utils::LerpColor(start.color, end.color, (y - start.pos.y) / (end.pos.y - start.pos.y))));
        if (D > 0)
        {
            x = x + xi;
            D = D + (2 * (dx - dy));
        }
        else D = D + 2 * dx;
    }
}

void Rasterizer::PlotLineLow(const Vertex& start, const Vertex& end)
{
    float dx = end.pos.x - start.pos.x;
    float dy = end.pos.y - start.pos.y;
    float yi = 1;
    const float numOfpoints = std::max(abs(dx), abs(dy)) + 1;

    if (dy < 0)
    {

        yi = -1;
        dy = -dy;
    }
    float D = (2 * dy) - dx;
    float y = start.pos.y;

    for (float x = start.pos.x; x <= end.pos.x; x++)
    {
        Rasterizer::DrawPixel(Vertex(Math::Vector3(x, y, 0), Utils::LerpColor(start.color, end.color, (x - start.pos.x) / (end.pos.x - start.pos.x))));
        if (D > 0)
        {
            y = y + yi;
            D = D + (2 * (dy - dx));
        }
        else D = D + 2 * dy;
    }
}

void Rasterizer::DrawPixel(const Vertex& v)
{
	if (v.pos.x < 0 || v.pos.x > screenWidth / Draw::GetPixelSize()) return;
	if (v.pos.y < 0 || v.pos.y > screenHeight / Draw::GetPixelSize()) return;
	Color temp = Draw::GetPixelColor();
	Draw::ChangePixelColor(v.color);
	Draw::DrawPixel(v.pos.x, v.pos.y);
	Draw::ChangePixelColor(temp);
}

void Rasterizer::DrawLine(const Vertex& v1, const Vertex& v2)
{
    if (abs(v1.pos.y - v2.pos.y) < abs(v1.pos.x - v2.pos.x))
    {
        if (v1.pos.x > v2.pos.x) PlotLineLow(v2, v1);
        else PlotLineLow(v1, v2);
    }
    else
    {
        if (v1.pos.y > v2.pos.y) PlotLineHigh(v2, v1);
        else PlotLineHigh(v1, v2);
    }
}

void Rasterizer::DrawTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3)
{
    DrawLine(v1, v2);
    DrawLine(v1, v3);
    DrawLine(v2, v3);
}

void Rasterizer::SetPixelColor(int r, int g, int b, int a)
{
	Color c = { (unsigned char)r, (unsigned char)g, (unsigned char)b, (unsigned char)a };
	Draw::ChangePixelColor(c);
}

void Rasterizer::SetPixelColor(const Color& c)
{
	Draw::ChangePixelColor(c);
}

Color& Rasterizer::GetPixelColor()
{
	return Draw::GetPixelColor();
}
