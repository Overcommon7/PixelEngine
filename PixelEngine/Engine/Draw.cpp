#include "pch.h"
#include "Draw.h"
#include "Defines.h"
#include "Utilities.h"
#include "Events.h"

void Draw::Initalize(int pixelDimension, int width, int height)
{
	if (pixelDimension == (int)pixel.width && 
		width == screenWidth * (int)pixel.width && 
		height == screenHeight * (int)pixel.width) return;

	int m = GetCurrentMonitor();
	monitorHeight = GetMonitorHeight(m);
	monitorWidth = GetMonitorWidth(m);
	pixelResolutionWidth = width / pixelDimension;
	pixelResolutionHeight = height / pixelDimension;
	pixelSize = pixelDimension;
	Events::OnScriptInit();
	ChangePixelSize(pixelDimension);
	SetPixelResolution(width, height);
}

void Draw::DrawScaledPixel(int x, int y)
{
	pixel.x = x * pixel.width;
	pixel.y = y * pixel.width;
	if (drawFakeWindow && (
		pixel.x < fakeWindow.x || pixel.x >= fakeWindow.width + fakeWindow.x ||
		pixel.y < fakeWindow.y || pixel.y >= fakeWindow.height + fakeWindow.y)) return;

	if (pixel.width <= 1.1f) DrawPixel(x, y, color);
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
	if (width < SCREEN_WIDTH * 0.75 || height < SCREEN_HEIGHT * 0.75)
	{
		drawFakeWindow = true;
		fakeWindow = { 0, 0, (float)width, (float)height };
	}
	else
	{
		drawFakeWindow = false;
		fakeWindow = {};
	}
	SetWindowSize(width, height);
	windowResized = true;
}

void Draw::Drawing()
{
	if (showGrid)
	{
		for (short i = pixel.width; i < pixelResolutionHeight * pixelSize; i += pixel.width)
			DrawLine(i, 0, i, pixelResolutionHeight * pixelSize, WHITE);
		for (short i = 0; i < pixelResolutionWidth * pixelSize; i += pixel.width)
			DrawLine(0, i, pixelResolutionWidth * pixelSize, i, WHITE);
	}

	if (drawFakeWindow)
		Utils::DrawRectangleLines(fakeWindow);
}
