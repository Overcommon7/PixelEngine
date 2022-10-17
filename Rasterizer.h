#pragma once
#include "Vertex.h"
enum class FillMode
{
    Solid,
    Wireframe
};

class Rasterizer
{
    Rasterizer() = delete;
    Rasterizer(const Rasterizer& p) = delete;
    Rasterizer& operator=(const Rasterizer& p) = delete;
    static void PlotLineHigh(const Vertex& start, const Vertex& end);
    static void PlotLineLow(const Vertex& start, const Vertex& end);
    static vector<Vertex> FillBetweenVerticies(const Vector3& vec, const Rectangle& rec, const float& totalArea, const Vertex& v1, const Vertex& v2, const Vertex& v3);
    static inline FillMode mode = FillMode::Solid;
public:
    static void DrawPixel(const Vertex& v);
    static void DrawLine(const Vertex& v1, const Vertex& v2);
    static void DrawTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3);
    static float AreaOfTriangle(const float& a, const float& b, const float& c);
    static void SetPixelColor(int r, int g, int b, int a = 255);
    static void SetPixelColor(const Color& c);
    static void SetFillMode(const FillMode& m) { mode = m; }
    static Color& GetPixelColor();
};

