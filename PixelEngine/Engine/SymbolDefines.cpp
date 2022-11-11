#include "pch.h"
#include "SymbolDefines.h"

extern int screenHeight = 500, screenWidth = 500;
extern int monitorWidth = 0, monitorHeight = 0;
extern const string workingDirectory = fs::current_path().generic_string() + '/';
extern bool windowResized = false, reCenterWindow = false;
extern bool launchTextEditor = false;
#ifdef _DEBUG
extern const string filepath = "../Scripts/";
#else
extern const string filepath = workingDirectory + "Scripts/";
#endif