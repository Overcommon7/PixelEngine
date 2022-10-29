#pragma once
#include "Defines.h" 

class Line
{
	inline static Color defaultColor = BLACK; 
	Color color;
	string text;
	Rectangle collider;
	float textWidthInPixels;

	float SetNewCollider();

public:

	Line(const float& lineSpacing, const int& lineNumber) : 
		color(defaultColor), text(""), textWidthInPixels(0), collider({ 0, (lineNumber * TEXT_SIZE) + (lineSpacing * lineNumber), 0, TEXT_SIZE}) {}

	Line(const Line& l) = default;
	Line& operator=(const Line& l) = default;

	//int Update(pair<int, int>& highlighted);
	float Update(int& index);
	void Draw() const;


	const Rectangle& GetCollider() const { return collider; }
	const string_view ViewText() const { return text; }
	const float& GetWidthInPixels() const { return textWidthInPixels; }


};

