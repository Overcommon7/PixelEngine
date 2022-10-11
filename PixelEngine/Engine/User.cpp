#include "pch.h"
#include "User.h"

void User::GetChar()
{
	static bool CapsLock = false;
	if (keyPressed == KEY_BACKSPACE) return;
	if (keyPressed < 32) return;
	if (keyPressed > 126) return;
	if (keyPressed == KEY_CAPS_LOCK)
	{
		CapsLock = !CapsLock;
		return;
	}
	if ((CapsLock || (IsKeyUp(KEY_LEFT_SHIFT) && IsKeyUp(KEY_RIGHT_SHIFT))) && isalpha(keyPressed))
		keyPressed += ((int)'a' - (int)'A');
	if ((IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) && isdigit(keyPressed))
		switch (keyPressed)
		{
		case '0':
			keyPressed = '(';
			break;
		case '1':
			keyPressed = ')';
			break;
		case '2':
			keyPressed = '@';
			break;
		case '3':
			keyPressed = '#';
			break;
		case '4':
			keyPressed = '$';
			break;
		case '5':
			keyPressed = '%';
			break;
		case '6':
			keyPressed = '^';
			break;
		case '7':
			keyPressed = '&';
			break;
		case '9':
			keyPressed = '(';
			break;
		default:
			return;
			break;
		}
}

void User::Update()
{
    keyPressed = GetKeyPressed();	
}
