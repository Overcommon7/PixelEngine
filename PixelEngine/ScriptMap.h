#pragma once
#include "UserScripts/AddVertex.h"
#include "UserScripts/EndDraw.h"
#include "UserScripts/BeginDraw.h"
#include "UserScripts/ChangeColor.h"
#include "DrawPixel.h"
#include "ToggleGrid.h"
#include "Init.h"
#include "Commands.h"

class ScriptMap
{
private:
    inline static const ADDVERTEX addvertex = {};
    inline static const ENDDRAW enddraw = {};
    inline static const BEGINDRAW begindraw = {};
    inline static const CHANGECOLOR changecolor = {};
    inline static const DRAWPIXEL drawpixel = {};
    inline static const ToggleGrid togglegrid = {};
    inline static const Init init = {};
	inline const static unordered_map<string, const Commands*> scripts =
	{
        { init.GetName(), &init},
        { togglegrid.GetName(), &togglegrid },
        { drawpixel.GetName(), &drawpixel },
        { changecolor.GetName(), &changecolor },
        { begindraw.GetName(), &begindraw },
        { enddraw.GetName(), &enddraw },
        { addvertex.GetName(), &addvertex },
	};
public:
	static void InvokeScript(const string& s, const vector<string>& params);
};
























































