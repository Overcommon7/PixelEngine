#include "pch.h"
#include "ButtonManager.h"
#include "Mouse.h"


#pragma region ButtonFunctions
static void LoadIntoScript()
{
	ButtonManager::GetScript()->operator=(ButtonManager::GetSelectedButton()->GetText());
	
}

static void CreateNewScript()
{
	int i = 1;
	const string newPix = "NewPixelScript";
	bool finished = false;
	while (fs::exists(fs::path(filepath + newPix + to_string(i) + ".txt")))
		i++;
	ofstream create(newPix + to_string(i) + ".txt");
	ButtonManager::GetScript()->operator=(newPix + to_string(i) + ".txt");
	create.close();
	while (!finished)
	{
		finished = true;
		try
		{
			fs::copy(workingDirectory + newPix + to_string(i) + ".txt", filepath);
		}
		catch (const std::exception&)
		{
			finished = false;
		}
	}
	fs::remove(newPix + to_string(i) + ".txt");
	fstream inFile(filepath + newPix + to_string(i) + ".txt");
	inFile << "Init(25, 30, 30)";
	inFile.close();
}
#pragma endregion

void ButtonManager::Initialize(string* s)
{
	script = s;
	Vector2 pos = { 0, 0 };
	buttons.clear();
	for (const auto& file : fs::recursive_directory_iterator(filepath))
	{
		buttons.push_back(Button(file.path().filename().generic_string(), pos, &LoadIntoScript));
		pos.y += BUTTON_HEIGHT;
	}
	buttons.push_back(Button("New File", pos, &CreateNewScript, GREEN));
}

void ButtonManager::Update()
{
	if (buttons.empty()) return;
	bool scroll = true;
	if (buttons.back().GetCollider().y + buttons.back().GetCollider().height < screenHeight && Mouse::GetMouseWheel() < 0)	scroll = false;
	if (buttons.front().GetCollider().y > 0 && Mouse::GetMouseWheel() > 0)	scroll = false;
	for (auto& button : buttons)
	{
		button.Update();
		if (button.IsClicked()) 
		{
			selectedButton = &button;
			button.InvokeOnClick();
			return;
		}
		if (scroll)	button.UpdatePosition({ 0, Mouse::GetMouseWheel() });
	}		
}

void ButtonManager::Draw()
{
	for (const auto& button : buttons)
		button.Draw();
}
