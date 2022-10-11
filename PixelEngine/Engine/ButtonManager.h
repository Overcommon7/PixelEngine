#pragma once
#include <vector>
#include "Button.h"

class ButtonManager
{
    inline static vector<Button> buttons = {};
    inline static string* script = {};
    inline static Button* selectedButton = {};
public:
    ButtonManager() = delete;
    ButtonManager(const ButtonManager& b) = delete;
    ButtonManager& operator=(const ButtonManager& b) = delete;
    static void Initialize(string* s);
    static void Update();
    static void Draw();
    static string* GetScript() { return script; }
    static Button* GetSelectedButton() { return selectedButton; }
};

