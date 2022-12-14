#include "pch.h"
#include "System.h"
#include "Application.h"
#include "Mouse.h"
#include "User.h"
#include "Defines.h"

void System::Initialize()
{
    InitWindow(screenWidth, screenHeight, "PixelEngie");
    SetExitKey(KEY_NULL);
    targetFPS = GetMonitorRefreshRate(GetCurrentMonitor());
    SetTargetFPS(targetFPS);
    
    engineFont = LoadFont("Engine/CandaraBold.ttf");
    Application::Initalize();
    Mouse::Initialize();
}

void System::Running()
{   
    system("cls");
    while (!WindowShouldClose())
    {
        SystemLogic();
        switch (state)
        {
        case ApplicationState::TitleScreen:
            Application::MenuLogic(state);
            break;
        case ApplicationState::Scripting:
            Application::Logic(state);
            break;
        }

        ClearBackground(Draw::GetBGColor());
        BeginDrawing();
        switch (state)
        {
        case ApplicationState::TitleScreen:
            Application::MenuDraw();
            break;
        case ApplicationState::Scripting:
            Application::Draw();
            break;
        }
        SystemDraw();
        EndDrawing();        
    }
}

int System::Shutdown()
{
    system("cls");
    Application::ShutDown();
    CloseWindow();
    return 0;
}

void System::SystemLogic()
{
    DT = GetFrameTime();
    if (windowResized || IsWindowResized()) OnResize();
    SetWindowTitle((to_string(GetFPS()) + "FPS").c_str());   
    Mouse::Update();
    User::Update();
    Draw::ChangePixelColor(WHITE);
    windowResized = false;
}

void System::OnResize()
{
    screenHeight = GetScreenHeight();
    screenWidth = GetScreenWidth();
    if (!reCenterWindow) return;
    int x = monitorWidth * 0.5;
    int y = monitorHeight * 0.5;
    x -= screenWidth * 0.5;
    y -= screenHeight * 0.5;
    SetWindowPosition(x, y);
}

void System::SystemDraw()
{
    if (state != ApplicationState::Scripting) return;
    Draw::Drawing();
    
}

int System::Run()
{
    Initialize();
    Running();
    return Shutdown();
}
