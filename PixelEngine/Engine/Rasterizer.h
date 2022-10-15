#pragma once
#include "Vertex.h"

class Rasterizer
{
    Rasterizer() = delete;
    Rasterizer(const Rasterizer& p) = delete;
    Rasterizer& operator=(const Rasterizer& p) = delete;
    static void PlotLineHigh(const Vertex& start, const Vertex& end);
    static void PlotLineLow(const Vertex& start, const Vertex& end);
public:
    static void DrawPixel(const Vertex& v);
    static void DrawLine(const Vertex& v1, const Vertex& v2);
    static void DrawTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3);
    static void SetPixelColor(int r, int g, int b, int a = 255);
    static void SetPixelColor(const Color& c);
    static Color& GetPixelColor();
};

