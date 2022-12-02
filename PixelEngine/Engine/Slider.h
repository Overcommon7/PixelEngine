#pragma once
#include "ScriptManager.h"
#include "Defines.h"

class Slider
{
	Rectangle dragArea;
	string variableName;
	string displayName;

	inline static float increment = 5.5f;

public:
	Slider() = default;
	Slider(const float& y, const string& variable) : dragArea({ 0, y, SLIDER_WIDTH, SLIDER_HIEGHT }), variableName(variable) 
	{
		displayName = variable;
		if (variable.length() <= 14) return;
		string temp = displayName.substr(displayName.length() - 2);
		displayName.erase(displayName.begin() + 3, displayName.end());
		displayName += "..." + temp;
	}
	Slider(const Slider& s) = default;
	Slider& operator=(const Slider& s) = default;

	void Draw() const;
	bool Update();
	void ChangeYPosition(const float& y) { dragArea.y += y; }
	const Rectangle& GetCollider() const { return dragArea; }

	static void UpdateIncrement(const float& f) { increment += f; if (increment < 0.5f) increment = 0.5f; else if (increment > 10.f) increment = 10.f; }
	static const string GetIncrement();
};