#pragma once
#include "UserScripts/PlaceDiamond.h"
#include "UserScripts/PlaceTriangle.h"
#include "UserScripts/DrawBox.h"
#include "UserScripts/ChangeColor.h"
#include "PlacePixel.h"
#include "ToggleGrid.h"
#include "Init.h"
#include "Commands.h"

class ScriptMap
{
private:
    inline static PlaceDiamond placediamond = {};
    inline static PlaceTriangle placetriangle = {};
    inline static DrawBox drawbox = {};
    inline static ChangeColor changecolor = {};
    inline static PlacePixel placepixel = {};
    inline static ToggleGrid togglegrid = {};
    inline static Init init = {};
	inline static unordered_map<string, Commands*> scripts =
	{
        { Init().GetName(), &init },
        { ToggleGrid().GetName(), &togglegrid },
        { PlacePixel().GetName(), &placepixel },
        { ChangeColor().GetName(), &changecolor },
        { DrawBox().GetName(), &drawbox },
        { PlaceTriangle().GetName(), &placetriangle },
        { PlaceDiamond().GetName(), &placediamond },
	};
public:
	ScriptMap() = delete;
	ScriptMap(const ScriptMap& s) = delete;
	ScriptMap& operator=(const ScriptMap& s) = delete;

	static void InvokeScript(const string& s, const vector<string>& params);
};






















