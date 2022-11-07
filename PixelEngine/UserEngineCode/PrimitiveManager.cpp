#include "pch.h"
#include "PrimitiveManager.h"
#include "Rasterizer.h"
#include "Clipper.h"
#include "MatrixStack.h"
#include "Camera.h"

Matrix4 PrimitiveManager::GetScreenTransform()
{
    float hw = screenWidth * 0.5f;
    float hh = screenHeight * 0.5f;

    return Matrix4{
        hw, 0, 0, 0,
        0, -hh, 0, 0,
        0, 0, 1, 1,
        hw, hh, 0, 1
    };
}

bool PrimitiveManager::EndDraw(bool applyTransform)
{
    if (!mBeginDraw) return false;

    if (applyTransform)
    {
        Matrix4 matFinal = MatrixStack::GetTransform() * PixelCamera::GetViewMatrix() * PixelCamera::GetProjectionMatrix() * GetScreenTransform();
        for (auto& v : vertexBuffer)
            v.pos = matFinal.TransformCoord(v.pos.Convert());
    }
    
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
    mApplyTransform = false;
    vertexBuffer.clear();
    return true;
}


