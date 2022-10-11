#pragma once
class System
{
    System() = delete;
    System(const System& s) = delete;
    System& operator=(const System& s) = delete;   

    inline static int targetFPS = 0;
    inline static ApplicationState state = ApplicationState::TitleScreen;

    static void Initialize();
    static void Running();
    static int Shutdown();
    static void SystemLogic();
    static void OnResize();
    static void SystemDraw();
public:
    static int Run();
};