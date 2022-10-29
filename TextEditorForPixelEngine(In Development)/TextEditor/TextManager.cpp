#include "pch.h"
#include "TextManager.h"
#include "Clicker.h"
#include "User.h"
#include "HotKeyManager.h"

void TextManager::Initialize()
{
	lines.push_back(new Line(linePadding, 0));
}

void TextManager::ShutDown()
{
	for (auto& line : lines)
	{
		delete line;
		line = nullptr;
	}
}

void TextManager::Update()
{
	if (lineIndex < 0 || lineIndex >= lines.size()) return;
	
	if (Mouse::LeftClick()) GetIndexesFromClick();
	else cursor.x += lines[lineIndex]->Update(textIndex);		
}

void TextManager::Draw()
{
	for (const auto& line : lines)
		line->Draw();

	DrawText(to_string(textIndex).c_str(), 0, SCREEN_HEIGHT - 30, 20.f, BLACK);
	DrawLine(cursor.x, lines[lineIndex]->GetCollider().y, cursor.x, lines[lineIndex]->GetCollider().y + TEXT_SIZE, BLACK);
}

void TextManager::GetIndexesFromClick()
{
	bool valid = false;
	int i = 0;
	for (;i < lines.size(); i++)
		if (CheckCollisionRecs(Mouse::GetPointer(), lines[i]->GetCollider()))
		{
			valid = true;
			break;
		}
	if (!valid)
	{
		textIndex = lines[lineIndex]->ViewText().length() - 1;
		return;
	}

	lineIndex = 0;
	while (lines[i] != lines[lineIndex]) ++lineIndex;

	float segment = lines[i]->GetWidthInPixels() / (float)lines[i]->ViewText().length();
	for (int j = 0; Mouse::GetPosition().x > segment * j; j++) 
		textIndex = j;

	if (Mouse::GetPosition().x < segment) cursor.x = 0;
	else cursor.x = Mouse::GetPosition().x - ((int)Mouse::GetPosition().x % (int)segment);
		
}

void TextManager::HandleHotKeys()
{
	switch (HotKeyManager::GetHotKeyExecuted())
	{
	case Action::Save:

		break;
	case Action::SaveAs:
		break;
	case Action::Copy:
		break;
	case Action::Paste:
		break;
	case Action::Cut:
		break;
	case Action::Duplicate:
		break;
	case Action::MoveLeft:
		break;
	case Action::MoveRight:
	case Action::None:
	default:
		return;
		break;
	}
}
