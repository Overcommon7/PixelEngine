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

vector<Vertex> Rasterizer::FillBetweenVerticies(const Vector3& vec, const Vector2& X, const float y, const float& totalArea, const Vertex& v1, const Vertex& v2, const Vertex& v3)
{
    vector<Vertex> verticies;
    verticies.reserve(X.y);
    for (float x = X.x; x < X.x + X.y; x++)
    {
        auto point = Math::Vector2(x, y);
        float AP = Math::Vector2(point - Math::Vector2(v1.pos.x, v1.pos.y)).Magnitude();
        float BP = Math::Vector2(point - Math::Vector2(v2.pos.x, v2.pos.y)).Magnitude();
        float CP = Math::Vector2(point - Math::Vector2(v3.pos.x, v3.pos.y)).Magnitude();
        float area = Rasterizer::AreaOfTriangle(AP, BP, vec.x) + Rasterizer::AreaOfTriangle(BP, CP, vec.y) + Rasterizer::AreaOfTriangle(AP, CP, vec.z);
        if (area <= totalArea + 0.5f && area >= totalArea - 0.5f)
        {
            auto c1 = v1.GetColorAsVector3() * (1 - (AP / std::max(vec.x, vec.z)));
            auto c2 = v2.GetColorAsVector3() * (1 - (BP / std::max(vec.x, vec.y)));
            auto c3 = v3.GetColorAsVector3() * (1 - (CP / std::max(vec.y, vec.z)));
            auto color = c1 + c2 + c3;
            Color c = { (unsigned char)std::min(color.x, 255.f), (unsigned char)std::min(color.y, 255.f), (unsigned char)std::min(color.z, 255.f), 255 };
            verticies.push_back(Vertex({ x, y }, c));
        }
    }
    return verticies;
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

    const float
        a = Math::Vector2(Math::Vector2(v1.pos.x, v1.pos.y) - Math::Vector2(v2.pos.x, v2.pos.y)).Magnitude(),
        b = Math::Vector2(Math::Vector2(v2.pos.x, v2.pos.y) - Math::Vector2(v3.pos.x, v3.pos.y)).Magnitude(),
        c = Math::Vector2(Math::Vector2(v3.pos.x, v3.pos.y) - Math::Vector2(v1.pos.x, v1.pos.y)).Magnitude();
    if (a + b <= c || a + c <= b || b + c <= a) return;
    const float totalArea = AreaOfTriangle(a, b, c);
    /* float base = std::max(std::max(a, b), c);
     float height = (2 * totalArea) / base;*/
    const Rectangle rec = {
        std::min(std::min(v1.pos.x, v2.pos.x), v3.pos.x),
        std::min(std::min(v1.pos.y, v2.pos.y), v3.pos.y),
        std::max(std::max(v1.pos.x, v2.pos.x), v3.pos.x),
        std::max(std::max(v1.pos.y, v2.pos.y), v3.pos.y)
    };

    if (mode == FillMode::Solid)
    {
        vector<future<vector<Vertex>>> futures;
        futures.reserve(rec.height);
        for (float y = rec.y; y < rec.y + rec.height; y++)
            futures.push_back(async(std::launch::async, FillBetweenVerticies, Vector3(a, b, c), Vector2(rec.x, rec.width), y, totalArea, v1, v2, v3));

        for (const auto& f : futures)
            if (f.valid()) f.wait();

        for (auto& fut : futures)
            for (const auto& f : fut.get())
                DrawPixel(f);
        futures.clear();
        futures.shrink_to_fit();
    }

    DrawLine(v1, v2);
    DrawLine(v1, v3);
    DrawLine(v2, v3);
}

float Rasterizer::AreaOfTriangle(const float& a, const float& b, const float& c)
{
    float s = (a + b + c) * 0.5f;
    return sqrtf(s * ((s - a) * (s - b) * (s - c)));
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
