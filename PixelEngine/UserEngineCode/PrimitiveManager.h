#pragma once
#include "Vertex.h"
#include "Matrix4.h"

enum class Topolgy
{
    Point,
    Line,
    Triangle
};

enum class Cullmode
{
    None,
    Front, 
    Back
};

class PrimitiveManager
{
    PrimitiveManager() = delete;
    PrimitiveManager(const PrimitiveManager& p) = delete;
    PrimitiveManager& operator=(const PrimitiveManager& p) = delete;
    static inline vector<Vertex> vertexBuffer = {};
    static inline Topolgy mTopology = Topolgy::Triangle;
    static inline bool mBeginDraw = false;
    inline static bool mApplyTransform = false;
    inline static bool mCorrectUV = false;
    inline static Cullmode cullmode = Cullmode::None;
    static Matrix4 GetScreenTransform();

public:
    static void AddVertex(const Vertex& vertex)
    {
        vertexBuffer.push_back(vertex);
    }

    static void BeginDraw(const Topolgy& mode)
    {
        mTopology = mode;
        mBeginDraw = true;
    }
    static void SetCullmode(const Cullmode& cm) { cullmode = cm; }
    static bool EndDraw(bool applyTransform = false);
    static void OnNewFrame();
};

