#include "pch.h"
#include "DepthBuffer.h"
#include "Defines.h"

void DepthBuffer::Initialize()
{
	depthBuffer = std::make_unique<float[]>(pixelResolutionHeight * pixelResolutionWidth);
	Update();
}

void DepthBuffer::Update()
{
	enabled = false;
	for (int i = 0; i < pixelResolutionHeight * pixelResolutionWidth; i++)
		depthBuffer[i] = 1.f;
}

bool DepthBuffer::CheckDepthBuffer(int x, int y, float depth)
{
	if (!enabled)
		return true;

	if (x >= 0 && x < pixelResolutionWidth &&
		y >= 0 && y < pixelResolutionHeight)
	{
		const int index = x + (y * pixelResolutionWidth);
		if (depth <= depthBuffer[index])
		{
			depthBuffer[index] = depth;
			return true;
		}
	}
	return false;
}
