#include "pch.h"
#include "Button.h"
#include "Mouse.h"
#include "Utilities.h"
#include "Defines.h"

void Button::Update()
{
	isHovering = CheckCollisionRecs(Mouse::GetPointer(), collider);
	isClicked = false;
	if (!isHovering) return;
	isClicked = Mouse::LeftClick();
}

void Button::Draw() const
{
	if (collider.y + collider.height < -1 || collider.y > screenHeight + 1) return;
	Utils::DrawRectangle(collider, color);
	if (isHovering)	Utils::DrawRectangle(collider, { 120, 120, 120, 120 });
	Utils::DrawRectangleLines(collider, BLACK);
	DrawTextEx(engineFont, text.c_str(), { collider.x + 5, collider.y + 5 }, 15, 1, BLACK);
}

void Button::UpdatePosition(const Vector2& vec)
{
	collider.x += vec.x;
	collider.y += vec.y;
}
