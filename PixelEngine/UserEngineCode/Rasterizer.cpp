#include "pch.h"
#include "Rasterizer.h"
#include "Defines.h"
#include "Draw.h"
#include "Utilities.h"
#include "DepthBuffer.h"
#include "TextureCache.h"

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
        float t = (y - start.pos.y) / (end.pos.y - start.pos.y);
        float z = std::lerp(start.pos.y, end.pos.y, t);
        Rasterizer::DrawScaledPixel(Vertex(Math::Vector3(x, y, z), Utils::LerpColor(start.color, end.color, t)));
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

    if (dy < 0)
    {

        yi = -1;
        dy = -dy;
    }
    float D = (2 * dy) - dx;
    float y = start.pos.y;

    for (float x = start.pos.x; x <= end.pos.x; x++)
    {
        float t = (x - start.pos.x) / (end.pos.x - start.pos.x);
        float z = std::lerp(start.pos.x, end.pos.x, t);
        Rasterizer::DrawScaledPixel(Vertex(Math::Vector3(x, y, z), Utils::LerpColor(start.color, end.color, t)));
        if (D > 0)
        {
            y = y + yi;
            D = D + (2 * (dy - dx));
        }
        else D = D + 2 * dy;
    }
}

void Rasterizer::FillBetweenVerticies(const Vector2& X, const float y, const Vertex& v1, const Vertex& v2, const Vertex& v3)
{
    for (float x = X.x; x < X.x + X.y; x++)
    {
        float wd = ((v2.pos.y - v3.pos.y) * (v1.pos.x - v3.pos.x)) + ((v3.pos.x - v2.pos.x) * (v1.pos.y - v3.pos.y));
        float w1n = ((v2.pos.y - v3.pos.y) * (x - v3.pos.x)) + ((v3.pos.x - v2.pos.x) * (y - v3.pos.y));
        float w2n = ((v3.pos.y - v1.pos.y) * (x - v3.pos.x)) + ((v1.pos.x - v3.pos.x) * (y - v3.pos.y));

        float w1 = w1n / wd;
        float w2 = w2n / wd;
        float w3 = 1 - w1 - w2;

        if (w1 >= 0 && w2 >= 0 && w3 >= 0)
        {
            auto c1 = v1.color * w1;
            auto c2 = v2.color * w2;
            auto c3 = v3.color * w3;
            float z1 = v1.pos.z * w1;
            float z2 = v2.pos.z * w2;
            float z3 = v3.pos.z * w3;
            float z = z1 + z2 + z3;
            auto color = c1 + c2 + c3;
            m.lock();
            pixels.push_back(Vertex({ x, y, z }, color));
            m.unlock();
        }
    }
}

void Rasterizer::DrawScaledPixel(const Vertex& v)
{
    if (v.pos.x < 0 || v.pos.x > screenWidth / Draw::GetPixelSize()) return;
    if (v.pos.y < 0 || v.pos.y > screenHeight / Draw::GetPixelSize()) return;
    if (!DepthBuffer::CheckDepthBuffer(v.pos.x, v.pos.y, v.pos.z)) return;
    Math::Color temp = Draw::GetPixelColor();
    Draw::ChangePixelColor(v.color);
    Draw::DrawScaledPixel(v.pos.x, v.pos.y);
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
    const Rectangle rec = {
        std::min(std::min(v1.pos.x, v2.pos.x), v3.pos.x),
        std::min(std::min(v1.pos.y, v2.pos.y), v3.pos.y),
        std::max(std::max(v1.pos.x, v2.pos.x), v3.pos.x),
        std::max(std::max(v1.pos.y, v2.pos.y), v3.pos.y)
    };

    if (mode == FillMode::Solid)
    {
        vector<float> Ys(rec.height);
        pixels.clear();
        if (pixels.capacity() < rec.width * rec.height * 0.5f);
        pixels.reserve(rec.width * rec.height * 0.5f);

        std::iota(Ys.begin(), Ys.end(), rec.y);
        std::for_each(std::execution::par, Ys.begin(), Ys.end(), [&v1, &v2, &v3, &rec](const float& y) {
            FillBetweenVerticies(Vector2(rec.x, rec.width), y, v1, v2, v3);
            });
        for (const auto& pix : pixels)
            DrawScaledPixel(pix);
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

void Rasterizer::SetPixelColor(const float& r, const float& g, const float& b, const float& a)
{
    Math::Color c = Math::Color( r, g, b, a );
    Draw::ChangePixelColor(c);
}

void Rasterizer::SetPixelColor(const Math::Color& c)
{
    Draw::ChangePixelColor(c);
}

Math::Color& Rasterizer::GetPixelColor()
{
    return Draw::GetPixelColor();
}
