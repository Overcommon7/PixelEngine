#include "pch.h"
#include "Application.h"
#include "ScriptManager.h"


void Application::SaveNewScreenShot()
{
	int i = 1;
	string temp = scriptFile.substr(0, scriptFile.find_last_of('.'));
	string name = screenshotPath + temp + to_string(i) + ".png";
	while (fs::exists(fs::path(name)))
	{
		i++;
		name = screenshotPath + temp + to_string(i) + ".png";
	}
		
	TakeScreenshot((temp + to_string(i) + ".png").c_str());
	bool ready = false;
	while (!ready)
	{
		ready = true;
		try
		{
			fs::copy(temp + to_string(i) + ".png", screenshotPath);
		}
		catch (const std::exception&)
		{
			ready = false;
		}
	}
	ready = false;
	while (!ready)
	{
		ready = true;
		try
		{
			fs::remove(temp + to_string(i) + ".png");
		}
		catch (const std::exception&)
		{
			ready = false;
		}
	}
	
}

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
	if (User::GetKey() == KEY_F10) SaveNewScreenShot();
	if (User::GetKey() != KEY_ESCAPE) return;
	system("cls");
	scriptFile.clear();
	Draw::SetBGColor(WHITE);
	SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	state = ApplicationState::TitleScreen;
}

void Application::Draw()
{
	ScriptManager::RunScripts();
}