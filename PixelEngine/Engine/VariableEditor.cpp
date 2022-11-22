#include "pch.h"
#include "VariableEditor.h"

void VariableEditor::Draw()
{
	if (!isActive) return;
	for (const auto& slider : sliders)
		slider.Draw();
}

bool VariableEditor::Update()
{
	if (!isActive) return false;
	for (auto& slider : sliders)
		if (slider.Update()) return true;
	return false;
}

void VariableEditor::OnScriptLoaded()
{
	//isActive = false;
	sliders.clear();
	sliders.reserve(ScriptManager::Variables().size());
	float y = 25.f;
	for (const auto& var : ScriptManager::Variables())
	{
		sliders.push_back(Slider(y, var.first));
		y += SLIDER_HIEGHT;
	}	
}
