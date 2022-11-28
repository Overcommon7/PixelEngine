#include "pch.h"
#include "Slider.h"
#include "Utilities.h"
#include "Mouse.h"
#include "Defines.h"

void Slider::Draw() const
{
	Utils::DrawRectangle(dragArea, {120, 120, 120, 70});
	string temp = ScriptManager::Variables().at(variableName).GetStringValue();
	auto pos = temp.find('.');
	if (pos != string::npos && pos + 3 < temp.length())
		temp.erase(temp.begin() + temp.find('.') + 3, temp.end());
	DrawTextEx(engineFont, (displayName + " - " + temp).c_str(), { dragArea.x + 10, dragArea.y + 10 }, 18.f, 1.f, WHITE);
	Utils::DrawRectangleLines(dragArea, BLACK);
}

bool Slider::Update()
{
	if (!Mouse::LeftDown())	return false;
	if (!CheckCollisionPointRec(Mouse::GetPosition(), dragArea)) return false;

	float amount = GetMouseDelta().x * DT * 7.5;
	ScriptManager::Variables().at(variableName).AddTo(amount);
	ScriptManager::Variables().at(variableName).ChangeResetValue(ScriptManager::Variables().at(variableName).GetValue());
	return true;
}
