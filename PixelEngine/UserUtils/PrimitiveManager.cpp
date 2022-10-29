#include "pch.h"
#include "PrimitiveManager.h"
#include "Rasterizer.h"
#include "Clipper.h"

bool PrimitiveManager::EndDraw()
{
    if (!mBeginDraw) return false;
    switch (mTopology)
    {
    case Topolgy::Point:
        for (int i = 0; i < vertexBuffer.size(); i++)
        {
            Rasterizer::DrawScaledPixel(vertexBuffer[i]);
        }
        break;
    case Topolgy::Line:
        for (int i = 1; i < vertexBuffer.size(); i += 2)
        {
            if (Clipper::ClipLine(vertexBuffer[i - 1], vertexBuffer[i]))
                Rasterizer::DrawLine(vertexBuffer[i - 1], vertexBuffer[i]);
        }
        break;
    case Topolgy::Triangle:
        for (int i = 2; i < vertexBuffer.size(); i += 3)
        {
            vector<Vertex> verticies = { vertexBuffer[i - 2], vertexBuffer[i - 1], vertexBuffer[i] };
            if (Clipper::ClipTriangle(verticies))
                for (int k = 2; k < verticies.size(); k++)     
                    Rasterizer::DrawTriangle(verticies.front(), verticies[k - 1], verticies[k]);
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

/*if (k % 2 == 0)
                  {
                      Draw::ChangePixelColor(WHITE);
                      verticies.front().color = Draw::GetPixelColor();
                      verticies[k - 1].color = Draw::GetPixelColor();
                      verticies[k].color = Draw::GetPixelColor();
                  }
                  else
                  {
                      Draw::ChangePixelColor(RED);
                      verticies.front().color = Draw::GetPixelColor();
                      verticies[k - 1].color = Draw::GetPixelColor();
                      verticies[k].color = Draw::GetPixelColor();
                  }*/