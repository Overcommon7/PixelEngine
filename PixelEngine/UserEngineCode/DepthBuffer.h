#pragma once
class DepthBuffer
{
    DepthBuffer() = delete;
    DepthBuffer(const DepthBuffer& d) = delete;
    DepthBuffer& operator=(const DepthBuffer& d) = delete;

    static inline unique_ptr<float[]> depthBuffer = {};
    static inline bool enabled = false;


public:
    static void Initialize();
    static void Update();
    static void SetEnabled(const bool e) { enabled = e; }
    static bool CheckDepthBuffer(int x, int y, float depth);

};

