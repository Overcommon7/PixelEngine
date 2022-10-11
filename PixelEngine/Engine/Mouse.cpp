#include "pch.h"
#include "Mouse.h"

void Mouse::UpdatePostition(float x, float y)
{
	collider.x = x;
	collider.y = y;
}

void Mouse::Update()
{
	UpdatePostition((float)GetMouseX(), (float)GetMouseY());
	leftClicked = LeftClicked();
	leftDown = LeftDowned();
	mouseWheel = GetMouseWheelMove() * 12.f;
	leftUp = IsMouseButtonUp(MOUSE_BUTTON_LEFT);
}

void Mouse::Initialize()
{
	collider = { (float)GetMouseX(), (float)GetMouseY(), 3.f, 3.f };
}

