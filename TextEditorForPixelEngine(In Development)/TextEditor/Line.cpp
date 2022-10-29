#include "pch.h"
#include "Line.h"
#include "User.h"
#include "Clicker.h"
#include "Utils.h"



float Line::SetNewCollider()
{
	float temp = textWidthInPixels;
	textWidthInPixels = MeasureTextEx(fonts.at(K_FONT_CANDARA), text.c_str(), TEXT_SIZE, 1.f).x;
	collider.width = textWidthInPixels;
	return textWidthInPixels - temp;
}

float Line::Update(int& index)
{
	if (User::GetKey() == '\0') return 0;
	auto it = text.begin();
	if (index < 0 || index > text.length()) return 0;
	if (User::GetKey() == KEY_BACKSPACE && !text.empty())
		it = text.erase(text.begin() + index - 1);
	else if (User::GetChar() == '\0') return 0;
	else
	{
		it = text.insert(text.begin() + index, User::GetChar());
		++it;
	}
	index = (int)std::distance(text.begin(), it);
	return SetNewCollider();	
}

void Line::Draw() const
{
	DrawTextEx(fonts.at(K_FONT_CANDARA), text.c_str(), { collider.x, collider.y }, TEXT_SIZE, 1.f, color);
	Utils::DrawRectangleLines(collider, RED);
}


