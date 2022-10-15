#pragma once
#include "Vertex.h"
enum class Topolgy
{
    Point,
    Line,
    Triangle
};

class PrimitiveManager
{
    PrimitiveManager() = delete;
    PrimitiveManager(const PrimitiveManager& p) = delete;
    PrimitiveManager& operator=(const PrimitiveManager& p) = delete;
    static inline vector<Vertex> vertexBuffer = {};
    static inline Topolgy mTopology = Topolgy::Triangle;
    static inline bool mBeginDraw = false;
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
    static bool EndDraw();    
};

