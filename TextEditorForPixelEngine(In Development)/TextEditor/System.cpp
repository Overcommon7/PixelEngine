#include "pch.h"
#include "System.h"
#include "Game.h"
#include "Defines.h"
#include "User.h"

extern unordered_map<string, Font> fonts;

void System::Initialize()
{
	//SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Default");
	InitAudioDevice();
	SetExitKey(KEY_NULL);
	targetFPS = GetMonitorRefreshRate(GetCurrentMonitor());
	SetTargetFPS(targetFPS);
	Mouse::Initialize();
	Game::Initialize();
	SetMouseCursor(MOUSE_CURSOR_IBEAM);
}

int System::ShutDown()
{
	SystemLogic();
	Game::ShutDown();
	SetMouseCursor(MOUSE_CURSOR_DEFAULT);
	CloseAudioDevice();
	CloseWindow();
	return 0;
}

void System::Application()
{
	while (!WindowShouldClose())
	{
		SystemLogic();

		switch (currentScreen)
		{
		case GameScreen::TilteScreen:
			Game::TitleScreenLogic(currentScreen);
			break;
		case GameScreen::Gameplay:
			Game::GameplayLogic(currentScreen);
			break;		
		case GameScreen::GameOver:
			Game::GameOverLogic(currentScreen);
			break;
		}

		BeginDrawing();
		ClearBackground(BGColor);

		switch (currentScreen)
		{
		case GameScreen::TilteScreen:
			Game::TitleScreenDraw();
			break;
		case GameScreen::Gameplay:
			Game::GameplayDraw();
			break;		
		case GameScreen::GameOver:
			Game::GameOverDraw();
			break;
		}

		SystemDraw();
		EndDrawing();
	}
}

void System::SystemLogic()
{
	DT = GetFrameTime();
	Mouse::Update();
	User::Update();		
}

void System::SystemDraw()
{
	
}

void System::Resize()
{
	SCREEN_WIDTH = GetScreenWidth();
	SCREEN_HEIGHT = GetScreenHeight();
	WINDOW_SCALE = SCREEN_WIDTH / MAX_WIDTH;
}

void System::ShowFPS()
{
	int fps = GetFPS();
	Color color = GREEN;
	if (fps < targetFPS * 0.5) color = YELLOW;
	if (fps < targetFPS * 0.25) color = RED;
	DrawTextEx(fonts.at(K_FONT_CANDARA), ("FPS " + to_string(fps)).c_str(), { 5.f, 5.f }, 15.f, 1.f, color);
}

int System::Run()
{
	Initialize();
	Application();
	return ShutDown();
}
