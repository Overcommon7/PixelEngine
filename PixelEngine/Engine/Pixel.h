#pragma once
class Pixel
{
    Pixel() = delete;
    Pixel(const Pixel& p) = delete;
    Pixel& operator=(const Pixel& p) = delete;
public:
    static void DrawPixel(int x, int y);
    static void SetPixelColor(int r, int g, int b, int a = 255);
    static void SetPixelColor(const Color& c);
    static Color& GetPixelColor();
};

