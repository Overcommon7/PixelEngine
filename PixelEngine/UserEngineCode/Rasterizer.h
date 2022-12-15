#pragma once
#include "Vertex.h"


enum class FillMode
{
    Solid,
    Wireframe
};

enum class ShadeMode
{
    Flat,
    Gouraud,
    Phong
};

class Rasterizer
{
    Rasterizer() = delete;
    Rasterizer(const Rasterizer& p) = delete;
    Rasterizer& operator=(const Rasterizer& p) = delete;
    static void PlotLineHigh(const Vertex& start, const Vertex& end);
    static void PlotLineLow(const Vertex& start, const Vertex& end);
    static void FillBetweenVerticies(const Vector2& X, const float y, const Vertex& v1, const Vertex& v2, const Vertex& v3);

    static inline ShadeMode shadeMode = ShadeMode::Gouraud;
    static inline FillMode mode = FillMode::Solid;
    static inline mutex m = {};
    static inline vector<Vertex> pixels = {};
public:
    static void DrawScaledPixel(const Vertex& v);
    static void DrawLine(const Vertex& v1, const Vertex& v2);
    static void DrawTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3);
    static float AreaOfTriangle(const float& a, const float& b, const float& c);
    static void SetPixelColor(const float& r, const float& g, const float& b, const float& a = 1);
    static void SetPixelColor(const Math::Color& c);
    static void SetFillMode(const FillMode& m) { mode = m; }
    static Math::Color& GetPixelColor();
    static const FillMode& GetFillMode() { return mode; }
    static void SetShadeMode(const ShadeMode& m) { shadeMode = m; }
    static const ShadeMode& GetShadeMode() { return shadeMode; }
};

