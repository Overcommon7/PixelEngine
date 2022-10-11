#include "pch.h"
#include "Application.h"
#include "ScriptManager.h"


void Application::Initalize()
{
	ButtonManager::Initialize(&scriptFile);
}

void Application::MenuLogic(ApplicationState& state)
{
	ButtonManager::Update();
	if (scriptFile.empty()) return;
	Draw::Initalize(20, 10, 10);
	Draw::SetBGColor(BLACK);
	ScriptManager::LoadScript(scriptFile);
	state = ApplicationState::Scripting;
}

void Application::MenuDraw()
{
	ButtonManager::Draw();
}

void Application::Logic(ApplicationState& state)
{
	ScriptManager::Update();
	if (User::GetKey() != KEY_ESCAPE) return;
	scriptFile.clear();
	Draw::SetBGColor(WHITE);
	SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	state = ApplicationState::TitleScreen;
}

void Application::Draw()
{
	ScriptManager::RunScripts();
}
