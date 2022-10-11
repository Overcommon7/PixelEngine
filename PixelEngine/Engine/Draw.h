#pragma once
class Draw
{
    Draw() = delete;
    Draw(const Draw& d) = delete;
    Draw& operator=(const Draw& d) = delete;
    
    static inline Rectangle pixel = { 1 };
    static inline Color color = WHITE;
    static inline Color bgColor = WHITE;
    static inline bool showGrid = false;
   
public:
    static void Initalize(int pixelSize, int width, int height);
    static void DrawPixel(int x, int y);
    static int GetPixelSize() { return (int)pixel.width; }
    static void ChangePixelColor(const Color& c);
    static void ChangePixelSize(int size);
    static void SetPixelResolution(int x, int y);
    static const Color& GetBGColor() { return bgColor; }
    static void SetBGColor(const Color& c) { bgColor = c; }
    static void ToggleGrid() { showGrid = !showGrid; }
    static void SetGrid(const bool& b) { showGrid = b; }
    static void Drawing();
    static Color& GetPixelColor() { return color; }
};

