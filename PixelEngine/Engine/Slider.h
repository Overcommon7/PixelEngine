#pragma once
#include "ScriptManager.h"
#include "Defines.h"

class Slider
{
	Rectangle dragArea;
	string variableName;
	string displayName;

public:
	Slider() = default;
	Slider(const float& y, const string& variable) : dragArea({ 0, y, SLIDER_WIDTH, SLIDER_HIEGHT }), variableName(variable) 
	{
		displayName = variable;
		if (variable.length() <= 9) return;
		string temp = displayName.substr(displayName.length() - 2);
		displayName.erase(displayName.begin() + 3, displayName.end());
		displayName += "..." + temp;
	}
	Slider(const Slider& s) = default;
	Slider& operator=(const Slider& s) = default;

	void Draw() const;
	bool Update();

};