#include "pch.h"
#include "PrimitiveManager.h"
#include "Rasterizer.h"
#include "Clipper.h"
#include "MatrixStack.h"
#include "Camera.h"

Matrix4 PrimitiveManager::GetScreenTransform()
{
    float hw = pixelResolutionWidth * 0.5f;
    float hh = pixelResolutionHeight * 0.5f;

    return Matrix4{
        hw, 0, 0, 0,
        0, -hh, 0, 0,
        0, 0, 1, 0,
        hw, hh, 0, 1
    };
}

bool PrimitiveManager::EndDraw(bool applyTransform)
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

        const Matrix4 matWorld = MatrixStack::GetTransform();
        const Matrix4 matView = PixelCamera::GetViewMatrix();
        const Matrix4 matProj = PixelCamera::GetProjectionMatrix();
        const Matrix4 matScreen = GetScreenTransform();
        const Matrix4 ndcSpace = matWorld * matView * matProj;
        const Matrix4 matFinal = ndcSpace * matScreen;

        for (int i = 2; i < vertexBuffer.size(); i += 3)
        {
            vector<Vertex> triangle = { vertexBuffer[i - 2], vertexBuffer[i - 1], vertexBuffer[i] };
            if (applyTransform)
            {
                if (cullmode != Cullmode::None)
                {
                    for (auto& t : triangle)
                        t.pos = ndcSpace.TransformCoord(t.pos);
                    Math::Vector3 faceNorm = Math::Vector3(triangle[1].pos - triangle[0].pos).CrossProduct(Math::Vector3(triangle[2].pos - triangle[0].pos));
                    if (cullmode == Cullmode::Back && faceNorm.z > 0.0f) continue;
                    if (cullmode == Cullmode::Front && faceNorm.z < 0.0f) continue;
                    for (auto& t : triangle)
                        t.pos = matScreen.TransformCoord(t.pos);
                }
                else
                {
                    for (auto& t : triangle)
                        t.pos = matFinal.TransformCoord(t.pos);
                }
            }
            
            if (Clipper::ClipTriangle(triangle))
                for (int k = 2; k < triangle.size(); k++)     
                    Rasterizer::DrawTriangle(triangle.front(), triangle[k - 1], triangle[k]);
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


