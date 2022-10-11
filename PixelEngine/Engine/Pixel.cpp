#include "pch.h"
#include "Pixel.h"
#include "Draw.h"
#include "Defines.h"

void Pixel::DrawPixel(int x, int y)
{
	if (x < 0 || x > screenWidth / Draw::GetPixelSize()) return;
	if (y < 0 || y > screenHeight / Draw::GetPixelSize()) return;
	Draw::DrawPixel(x, y);
}

void Pixel::SetPixelColor(int r, int g, int b, int a)
{
	Color c = { (unsigned char)r, (unsigned char)g, (unsigned char)b, (unsigned char)a };
	Draw::ChangePixelColor(c);
}

void Pixel::SetPixelColor(const Color& c)
{
	Draw::ChangePixelColor(c);
}

Color& Pixel::GetPixelColor()
{
	return Draw::GetPixelColor();
}
