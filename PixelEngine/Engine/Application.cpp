#include "pch.h"
#include "Application.h"
#include "ScriptManager.h"
#include "ScriptMap.h"
#include "VariableEditor.h"
#include "Defines.h"
#include "Events.h"


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
	ScriptMap::Initialize();
	int cm = GetCurrentMonitor();
	monitorHeight = GetMonitorHeight(cm);
	monitorWidth = GetMonitorWidth(cm);
}

void Application::MenuLogic(ApplicationState& state)
{
	if (User::GetKey() == KEY_F5) Initalize();	
	ButtonManager::Update();
	if (scriptFile.empty()) return;
	Draw::Initalize(20, 10, 10);
	Draw::SetBGColor(BLACK);
	ScriptManager::LoadScript(scriptFile);
	VariableEditor::OnScriptLoaded();
	Events::OnScriptLoaded();
	state = ApplicationState::Scripting;
}

void Application::MenuDraw()
{
	ButtonManager::Draw();
}

void Application::Logic(ApplicationState& state)
{
	bool refresh = VariableEditor::Update();
	bool scriptReloaded = refresh || User::GetKey() == KEY_F5;
	ScriptManager::Update(scriptReloaded, refresh);
	Events::OnNewFrame();
	if (User::GetKey() == KEY_F10) SaveNewScreenShot();
	if (User::GetKey() == KEY_F4 && !ScriptManager::Variables().empty()) VariableEditor::ToggleActive();
	if (User::GetKey() != KEY_ESCAPE) return;
	system("cls");
	scriptFile.clear();
	ScriptManager::Variables().clear();
	Draw::SetBGColor(WHITE);
	SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	windowResized = true;
	Application::Initalize();	
	state = ApplicationState::TitleScreen;
}

void Application::Draw()
{
	ScriptManager::RunScripts();
	Clipper::Draw();
	VariableEditor::Draw();
}

void Application::ShutDown()
{
	ScriptMap::ShutDown();
}


