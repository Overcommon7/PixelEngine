#pragma once
#include "Line.h"

class TextManager
{
    TextManager() = delete;
    TextManager(const TextManager& t) = delete;
    TextManager& operator=(const TextManager& t) = delete;

    inline static vector<Line*> lines = {};
    inline static float linePadding = 2.f;
    inline static int lineIndex = 0;
    inline static int textIndex = 0;
    inline static Vector2 cursor = {0, 0};

    static void GetIndexesFromClick();
    static void HandleHotKeys();

public:
    static void Initialize();
    static void ShutDown();
    static void Update();
    static void Draw();
};

