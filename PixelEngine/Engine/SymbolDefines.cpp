#include "pch.h"
#include "SymbolDefines.h"

//DO NOT TOUCH!!!!
#pragma region DO_NOT_TOUCH
extern int screenHeight = 500, screenWidth = 500;
extern int monitorWidth = 0, monitorHeight = 0;
extern const string workingDirectory = fs::current_path().generic_string() + '/';
extern bool windowResized = false;
extern Font engineFont = {};

extern int pixelResolutionWidth = 0, pixelResolutionHeight = 0;
extern int pixelSize = 0;
extern float DT = 0;
#ifdef _DEBUG
extern const string filepath = "../Scripts/";
#else
extern const string filepath = workingDirectory + "Scripts/";
#endif
#pragma endregion


//Change At Your Own Convinience
extern bool launchTextEditor = false, reCenterWindow = false;