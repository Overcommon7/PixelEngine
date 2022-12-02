#pragma once
class User
{
private:
	inline static int keyPressed = 0;
public:
	static const int& GetKey() { return keyPressed; }
	static const char GetChar();
	static void Update();
};

