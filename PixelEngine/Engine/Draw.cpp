#include "pch.h"
#include "Draw.h"
#include "Defines.h"
#include "Utilities.h"

void Draw::Initalize(int pixelSize, int width, int height)
{
	if (pixelSize == (int)pixel.width && 
		width == screenWidth * (int)pixel.width && 
		height == screenHeight * (int)pixel.width) return;

	int m = GetCurrentMonitor();
	monitorHeight = GetMonitorHeight(m);
	monitorWidth = GetMonitorWidth(m);
	ChangePixelSize(pixelSize);
	SetPixelResolution(width, height);
}

void Draw::DrawPixel(int x, int y)
{
	pixel.x = x * pixel.width;
	pixel.y = y * pixel.width;
	Utils::DrawRectangle(pixel, color);
}

void Draw::ChangePixelColor(const Color& c)
{
	color = c;
}

void Draw::ChangePixelSize(int size)
{
	pixel.width = size;
	pixel.height = size;
}

void Draw::SetPixelResolution(int x, int y)
{
	int width = x * pixel.width, height = y * pixel.width;
	if (width < 1) width = 1;
	if (width > monitorWidth) width = monitorWidth;
	if (height > monitorHeight) height = monitorHeight;
	SetWindowSize(width, height);
	windowResized = true;
}

void Draw::Drawing()
{
	if (showGrid)
	{
		for (short i = pixel.width; i < screenHeight; i += pixel.width)
			DrawLine(i, 0, i, screenHeight, WHITE);
		for (short i = 0; i < screenWidth; i += pixel.width)
			DrawLine(0, i, screenWidth, i, WHITE);	
	}
}
