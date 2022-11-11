#pragma once
#include "Defines.h"

class Button
{
	string text;
	Rectangle collider;
	bool isClicked;
	bool isHovering;
	function<void()> onClick;
	Color color;

public:
	Button(const string& txt, const Vector2& pos, function<void()> func, const Color& c = BLUE)
		: text(txt), collider({pos.x, pos.y, (float)SCREEN_WIDTH, BUTTON_HEIGHT }), onClick(func), isHovering(false), isClicked(false), color(c) {}
	Button(const string& txt, const Rectangle& rec, function<void()> func, const Color& c = BLUE) : text(txt), collider(rec), onClick(func), isHovering(false), isClicked(false), color(c) {}
	Button(const Button& b) = default;
	Button& operator=(const Button& b) = default;

	void Update();
	void Draw() const;
	void UpdatePosition(const Vector2& vec);
	const Rectangle& GetCollider() const { return collider; }
	const bool& IsClicked() const { return isClicked; }
	const string& GetText() const { return text; }
	void InvokeOnClick() const { onClick(); }
};
									 
