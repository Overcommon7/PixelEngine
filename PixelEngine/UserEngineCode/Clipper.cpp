#include "pch.h"
#include "Clipper.h"
#include "Utilities.h"

Vertex Clipper::ComputeIntersection(const Vertex& v1, const Vertex& v2, ClipEdge edge)
{
    Vertex retVal;
    float t;
    switch (edge)
    {
    case ClipEdge::Left:
        t = (viewport.x - v1.pos.x) / (v2.pos.x - v1.pos.x);
        break;
    case ClipEdge::Bottom:        
        t = ((viewport.y + viewport.height) - v1.pos.y) / (v2.pos.y - v1.pos.y);
        break;
    case ClipEdge::Right:
        t = ((viewport.x + viewport.width - 1) - v1.pos.x) / (v2.pos.x - v1.pos.x);
        break;
    case ClipEdge::Top:
        t = (viewport.y - v1.pos.y) / (v2.pos.y - v1.pos.y);
        break;
    default:
        break;
    }

    retVal.color = Utils::LerpColor(v1.color, v2.color, t);
    retVal.pos = v1.pos.Lerp(v2.pos, t);
    return retVal;
}

bool Clipper::IsInFront(const Vertex& v, ClipEdge edge)
{
    switch (edge)
    {
    case ClipEdge::Left:
        return v.pos.x > viewport.x;
        break;
    case ClipEdge::Bottom:
        return v.pos.y < viewport.y + viewport.height;
        break;
    case ClipEdge::Right:
        return v.pos.x < viewport.x + viewport.width;
        break;
    case ClipEdge::Top:
        return v.pos.y > viewport.y;
        break;
    case ClipEdge::Count:
    default:
        break;
    }
    return false;
}

void Clipper::Update()
{
    
}

void Clipper::Draw()
{
    if (!displayViewport) return;
    if (!mClipping) return;

    Rectangle vp = viewport;
    vp.x *= Draw::GetPixelSize();
    vp.y *= Draw::GetPixelSize();
    vp.width *= Draw::GetPixelSize();
    vp.height *= Draw::GetPixelSize();
    Utils::DrawRectangleLines(vp, color);
}

void Clipper::OnScriptInit()
{
    viewport = {};
    color = RED;
    displayViewport = false;
}

bool Clipper::ClipPoint(const Vertex& v)
{
    if (!mClipping) return true;
    if (v.pos.x < viewport.x || v.pos.x > viewport.x + viewport.width) return false;
    if (v.pos.y < viewport.y || v.pos.y > viewport.y + viewport.height) return false;
    return true;
}

bool Clipper::ClipLine(Vertex& v1, Vertex& v2)
{
    if (!mClipping) return true;
    double slope = 0;
    bool v1start = false;
    if (abs(v1.pos.y - v2.pos.y) < abs(v1.pos.x - v2.pos.x)) v1start = v1.pos.x < v2.pos.x;
    else v1start = v1.pos.y < v2.pos.y;
    if (v1start) slope = ((v1.pos.y - v2.pos.y) / (v1.pos.x - v2.pos.x));
    else slope = ((v2.pos.y - v1.pos.y) / (v2.pos.x - v1.pos.x));
    double b = v1.pos.y - (slope * v1.pos.x);

    double leftY, rightY, topX, bottomX;

    leftY = slope * viewport.x + b;
    rightY = slope * (viewport.x + viewport.width) + b;
    topX = (viewport.y - b) / slope;
    bottomX = ((viewport.y + viewport.height) - b) / slope;

    if (slope == NAN)
    {
        bottomX = v1.pos.x;
        topX = v1.pos.x;
    }
       
    vector<Vector2> positions;
    if (!(leftY > viewport.y + viewport.height || leftY < viewport.y))
        positions.push_back({ viewport.x, (float)leftY });
    if (!(rightY > viewport.y + viewport.height || rightY < viewport.y))
        positions.push_back({ viewport.x + viewport.width, (float)rightY });

    if (slope != NAN)
    {
        if (!(bottomX > viewport.x + viewport.width || bottomX < viewport.x))
            positions.push_back({ (float)bottomX, viewport.y + viewport.height - 1 });
        if (!(topX > viewport.x + viewport.width || topX < viewport.x))
            positions.push_back({ (float)topX, viewport.y });
    }
   
    float oldLength = Math::Vector3(v1.pos - v2.pos).Magnitude();
    Vertex oldV1 = v1;
    if (!ClipPoint(v1) && !positions.empty())
    {   
        float newLength = Math::Vector3(Math::Vector3(positions.front().x, positions.front().y, 0) - v1.pos).Magnitude();
        float t = newLength / oldLength;
        v1.color = Utils::LerpColor(v1.color, v2.color, t);
        v1.pos.x = positions.front().x;
        v1.pos.y = positions.front().y;
        
    }
    if (!ClipPoint(v2) && positions.size() >= 2)
    {
        float newLength = Math::Vector3(Math::Vector3(positions.back().x, positions.back().y, 0) - oldV1.pos).Magnitude();
        float t = newLength / oldLength;
        v2.color = Utils::LerpColor(oldV1.color, v2.color, t);
        v2.pos.x = positions.back().x;
        v2.pos.y = positions.back().y;
    }
    
   

    if (!ClipPoint(v1) && !ClipPoint(v2)) return false;
    return true;
}

bool Clipper::ClipTriangle(vector<Vertex>& vertices)
{
    if (!mClipping) return true;
    vector<Vertex> newVertices;
    for (int i = 0; i < (int)ClipEdge::Count; i++)
    {
        newVertices.clear();
        ClipEdge edge = (ClipEdge)i;
        for (int n = 0; n < vertices.size(); n++)
        {
            int k = (n + 1) % vertices.size();
            const Vertex& v1 = vertices[n];
            const Vertex& v2 = vertices[k];

            bool isInsideV1 = IsInFront(v1, edge);
            bool isInsideV2 = IsInFront(v2, edge);

            if (isInsideV1 != isInsideV2) newVertices.push_back(ComputeIntersection(v1, v2, edge));
            if (isInsideV2) newVertices.push_back(v2);

        }
        vertices = newVertices;
    }
    return vertices.size() >= 3;
}