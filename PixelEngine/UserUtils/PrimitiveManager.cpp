#include "pch.h"
#include "PrimitiveManager.h"
#include "Rasterizer.h"

bool PrimitiveManager::EndDraw()
{
    if (!mBeginDraw) return false;
    switch (mTopology)
    {
    case Topolgy::Point:
        for (int i = 0; i < vertexBuffer.size(); i++)
        {
            Rasterizer::DrawPixel(vertexBuffer[i]);
        }
        break;
    case Topolgy::Line:
        for (int i = 1; i < vertexBuffer.size(); i += 2)
        {
            Rasterizer::DrawLine(vertexBuffer[i - 1], vertexBuffer[i]);
        }
        break;
    case Topolgy::Triangle:
        for (int i = 2; i < vertexBuffer.size(); i += 3)
        {
            Rasterizer::DrawTriangle(vertexBuffer[i - 2], vertexBuffer[i - 1], vertexBuffer[i]);
        }
        break;
    default:
        mBeginDraw = false;
        return false;
        break;
    }
    mBeginDraw = false;
    vertexBuffer.clear();
    return true;
}
