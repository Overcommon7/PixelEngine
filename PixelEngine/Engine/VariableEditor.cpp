#include "pch.h"
#include "VariableEditor.h"
#include "Mouse.h"
#include "Defines.h"

void VariableEditor::Draw()
{
	if (!isActive) return;
	for (const auto& slider : sliders)
		slider.Draw();
	DrawTextEx(engineFont, ("Scroll Speed: " + Slider::GetIncrement()).c_str(), { screenWidth - 110.f, 10.f }, 12.f, 1.f, WHITE);
}

bool VariableEditor::Update()
{	
	if (!isActive) return false;
	isActive = !sliders.empty();

	bool noScroll = false;
	if (IsKeyDown(KEY_LEFT_SHIFT) && abs(Mouse::GetMouseWheel()) > 0)
	{
		Slider::UpdateIncrement(Mouse::GetMouseWheel() * DT);
		noScroll = true;
	}
		

	bool scroll = true;
	if (!noScroll && sliders.back().GetCollider().y + sliders.back().GetCollider().height < screenHeight && Mouse::GetMouseWheel() < 0) scroll = false;
	if (!noScroll && sliders.front().GetCollider().y > 0 && Mouse::GetMouseWheel() > 0) scroll = false;
	for (auto& slider : sliders)
	{
		if (slider.Update()) return true;
		if (scroll && !noScroll) slider.ChangeYPosition(Mouse::GetMouseWheel());
	}		
	return false;
}

void VariableEditor::OnScriptLoaded()
{
	isActive = false;
	sliders.clear();
	sliders.reserve(ScriptManager::Variables().size());
	float y = 25.f;
	for (const auto& var : ScriptManager::Variables())
	{
		sliders.push_back(Slider(y, var.first));
		y += SLIDER_HIEGHT;
	}	
}
