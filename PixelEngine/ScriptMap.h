#pragma once
#include "DrawPixel.h"
#include "ToggleGrid.h"
#include "Init.h"
#include "Commands.h"

class ScriptMap
{
private:
    inline static const DRAWPIXEL drawpixel = {};
    inline static const ToggleGrid togglegrid = {};
    inline static const Init init = {};

    //inline static const string file = "TextEditorCommands.txt";
	inline const static unordered_map<string, const Commands*> scripts =
	{
        { init.GetName(), &init},
        { togglegrid.GetName(), &togglegrid },
        { drawpixel.GetName(), &drawpixel },
	};
public:
	static void InvokeScript(const string& s, const vector<string>& params);
    static void Initialize();
    static void ShutDown();
};