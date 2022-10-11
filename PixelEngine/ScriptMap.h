#pragma once
#include "UserScripts/DrawTriangle.h"
#include "UserScripts/DrawLine.h"
#include "UserScripts/DrawRectangle.h"
#include "UserScripts/ChangeColor.h"
#include "UserScripts/PlaceDiamond.h"
#include "DrawPixel.h"
#include "ToggleGrid.h"
#include "Init.h"
#include "Commands.h"

class ScriptMap
{
private:
    inline static DRAWTRIANGLE drawtriangle = {};
    inline static DRAWLINE drawline = {};
    inline static DRAWRECTANGLE drawrectangle = {};
    inline static CHANGECOLOR changecolor = {};
    inline static PlaceDiamond placediamond = {};
    inline static DRAWPIXEL drawpixel = {};
    inline static ToggleGrid togglegrid = {};
    inline static Init init = {};
	inline static unordered_map<string, Commands*> scripts =
	{
        { Init().GetName(), &init },
        { ToggleGrid().GetName(), &togglegrid },
        { DRAWPIXEL().GetName(), &drawpixel },
        { PlaceDiamond().GetName(), &placediamond },
        { CHANGECOLOR().GetName(), &changecolor },
        { DRAWRECTANGLE().GetName(), &drawrectangle },
        { DRAWLINE().GetName(), &drawline },
        { DRAWTRIANGLE().GetName(), &drawtriangle },
	};
public:
	ScriptMap() = delete;
	ScriptMap(const ScriptMap& s) = delete;
	ScriptMap& operator=(const ScriptMap& s) = delete;

	static void InvokeScript(const string& s, const vector<string>& params);
};































