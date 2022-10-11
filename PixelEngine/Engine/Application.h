#pragma once
#include "Defines.h"
#include "Draw.h"
#include "Button.h"
#include "ButtonManager.h"

class Application
{
    Application() = delete;
    Application(const Application& a) = delete;
    Application& operator=(const Application& a) = delete;

    inline static string scriptFile = "";
public:
    static void Initalize();
    static void MenuLogic(ApplicationState& state);
    static void MenuDraw();
    static void Logic(ApplicationState& state);
    static void Draw();
};

