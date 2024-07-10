#pragma once
#include "Vertex.h"
#include "Defines.h"
#include "Draw.h"

enum class ClipEdge : int { Left, Bottom, Right, Top, Count };

struct Edge
{
    Vector2 start;
    Vector2 end;
};

class Clipper
{
    Clipper() = delete;
    Clipper(const Clipper& c) = delete;
    Clipper& operator=(const Clipper& c) = delete;

    static inline bool mClipping = true;
    static inline bool displayViewport = false;
    static inline Rectangle viewport = { 0, 0, 0, 0 };
    static inline Math::Color color = RED;

    static Vertex ComputeIntersection(const Vertex& v1, const Vertex& v2, ClipEdge edge);
    static bool IsInFront(const Vertex& v, ClipEdge edge);
    //static void SutherlandClip(vector<Vertex>& verticies, float x1, float x2, float y1, float y2);
public:

    static void Update();
    static void Draw();
    static void OnScriptInit();

    static bool ClipPoint(const Vertex& v);
    static bool ClipLine(Vertex& v1, Vertex& v2);
    static bool ClipTriangle(vector<Vertex>& vertices);

    static bool IsClipping() { return mClipping; }
    static void SetClipping(bool clip) { mClipping = clip; }
    static void SetViewport(const Rectangle& vp) { viewport = vp; }
    static void ShowViewport(bool show) { displayViewport = show; }
    static void SetViewportColor(const Math::Color& c) { color = c; }
    //static const Rectangle& GetViewport() { return viewport; }
};

