#include "pch.h"
#include "User.h"

const char User::GetChar()
{
	if (keyPressed == KEY_BACKSPACE) return '\0';
	if (keyPressed < 32) return '\0';
	if (keyPressed > 126) return '\0';
	if (keyPressed == KEY_CAPS_LOCK) 
	{
		CapsLock = !CapsLock;
		return '\0';
	}
	char value = '\0';
	if ((!CapsLock && (IsKeyUp(KEY_LEFT_SHIFT) && IsKeyUp(KEY_RIGHT_SHIFT))) && isalpha(keyPressed))
		value = tolower(keyPressed);
	else if ((IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)))
		switch (keyPressed)
		{
		case '0':
			value = '(';
			break;
		case '1':
			value = ')';
			break;
		case '2':
			value = '@';
			break;
		case '3':
			value = '#';
			break;
		case '4':
			value = '$';
			break;
		case '5':
			value = '%';
			break;
		case '6':
			value = '^';
			break;
		case '7':
			value = '&';
			break;
		case '9':
			value = '(';
			break;
		case '-':
			value = '_';
			break;
		case '=':
			value = '+';
			break;
		case '[':
			value = '{';
			break;
		case ']':
			value = '}';
			break;
		case ';':
			value = ':';
			break;
		case '\'':
			value = '>';
			break;
		case ',':
			value = '<';
			break;
		case '/':
			value = '?';
			break;
		case '\\':
			value = '|';
			break;
		default:
			break;
		}
	return value;
}

void User::Update()
{
    keyPressed = GetKeyPressed();
}
