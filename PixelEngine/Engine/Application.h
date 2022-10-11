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
    
#ifndef _DEBUG
    inline static const string screenshotPath = "ScreenShots/";
#else
    inline static const string screenshotPath = "../ScreenShots/";
#endif

    static void SaveNewScreenShot();
public:
    static void Initalize();
    static void MenuLogic(ApplicationState& state);
    static void MenuDraw();
    static void Logic(ApplicationState& state);
    static void Draw();
};

