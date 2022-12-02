#include "pch.h"
#include "User.h"

const char User::GetChar()
{
	static bool CapsLock = false;
	char key = keyPressed;
	if (key == KEY_BACKSPACE) return '\0';
	if (key < 32) return '\0';
	if (key >= KEY_KP_0 && key <= KEY_KP_9)
	{
		key -= 300;
		return key;
	}
	if (key > 126) return '\0';
	if (key == KEY_CAPS_LOCK)
	{
		CapsLock = !CapsLock;
		return '\0';
	}
	if ((CapsLock || (IsKeyUp(KEY_LEFT_SHIFT) && IsKeyUp(KEY_RIGHT_SHIFT))) && isalpha(key))
		key += ((int)'a' - (int)'A');
	if ((IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) && isdigit(key))
		switch (key)
		{
		case '0':
			key = '(';
			break;
		case '1':
			key = ')';
			break;
		case '2':
			key = '@';
			break;
		case '3':
			key = '#';
			break;
		case '4':
			key = '$';
			break;
		case '5':
			key = '%';
			break;
		case '6':
			key = '^';
			break;
		case '7':
			key = '&';
			break;
		case '9':
			key = '(';
			break;
		default:
			return '\0';
			break;
		}
	return key;
}

void User::Update()
{
    keyPressed = GetKeyPressed();
	
}
