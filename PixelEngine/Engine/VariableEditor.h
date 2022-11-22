#pragma once
#include "Slider.h"
class VariableEditor
{
    inline static bool isActive = true;
    inline static vector<Slider> sliders = {};
public:
    VariableEditor() = delete;
    VariableEditor(const VariableEditor& v) = delete;
    VariableEditor& operator=(const VariableEditor& v) = delete;

    static void Draw();
    static bool Update();
    static void OnScriptLoaded();
    static void SetActive(const bool& a) { isActive = a; }
    static void ToggleActive() { isActive = !isActive; }

};

