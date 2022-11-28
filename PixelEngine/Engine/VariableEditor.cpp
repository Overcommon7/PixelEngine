#include "pch.h"
#include "VariableEditor.h"
#include "Mouse.h"

void VariableEditor::Draw()
{
	if (!isActive) return;
	for (const auto& slider : sliders)
		slider.Draw();
}

bool VariableEditor::Update()
{
	if (!isActive) return false;
	bool scroll = true;
	if (sliders.back().GetCollider().y + sliders.back().GetCollider().height < screenHeight && Mouse::GetMouseWheel() < 0) scroll = false;
	if (sliders.front().GetCollider().y > 0 && Mouse::GetMouseWheel() > 0) scroll = false;
	for (auto& slider : sliders)
	{
		if (slider.Update()) return true;
		if (scroll) slider.ChangeYPosition(Mouse::GetMouseWheel());
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
