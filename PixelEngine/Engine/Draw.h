#pragma once


class Draw
{
    Draw() = delete;
    Draw(const Draw& d) = delete;
    Draw& operator=(const Draw& d) = delete;
    
    static inline Rectangle pixel = { 1 };
    static inline Math::Color color = WHITE;
    static inline Color bgColor = WHITE;
    static inline bool showGrid = false;
    static inline Rectangle fakeWindow = {};
    static inline bool drawFakeWindow = false;
   
public:
    static void Initalize(int pixelDimension, int width, int height);
    static void DrawScaledPixel(int x, int y);
    static int GetPixelSize() { return (int)pixel.width; }
    static void ChangePixelColor(const Math::Color& c);
    static void ChangePixelSize(int size);
    static void SetPixelResolution(int x, int y);
    static const Color& GetBGColor() { return bgColor; }
    static void SetBGColor(const Math::Color& c) { bgColor = c; }
    static void ToggleGrid() { showGrid = !showGrid; }
    static void SetGrid(const bool& b) { showGrid = b; }
    static void Drawing();
    static Math::Color& GetPixelColor() { return color; }
};

