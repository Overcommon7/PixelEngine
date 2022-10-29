#pragma once
#include "UserCommands/SetClipping.h"
#include "UserCommands/ShowViewport.h"
#include "UserCommands/SetViewport.h"
#include "UserCommands/SetFillMode.h"
#include "UserCommands/AddVertex.h"
#include "UserCommands/EndDraw.h"
#include "UserCommands/BeginDraw.h"
#include "UserCommands/ChangeColor.h"
#include "DrawPixel.h"
#include "ToggleGrid.h"
#include "Init.h"
#include "Commands.h"

class ScriptMap
{
private:
    inline static const SETCLIPPING setclipping = {};
    inline static const SHOWVIEWPORT showviewport = {};
    inline static const SETVIEWPORT setviewport = {};
    inline static const SETFILLMODE setfillmode = {};
    inline static const ADDVERTEX addvertex = {};
    inline static const ENDDRAW enddraw = {};
    inline static const BEGINDRAW begindraw = {};
    inline static const CHANGECOLOR changecolor = {};
    inline static const DRAWPIXEL drawpixel = {};
    inline static const ToggleGrid togglegrid = {};
    inline static const Init init = {};
    inline static const string file = "TextEditorCommands.txt";
	inline const static unordered_map<string, const Commands*> scripts =
	{
        { init.GetName(), &init},
        { togglegrid.GetName(), &togglegrid },
        { drawpixel.GetName(), &drawpixel },
        { changecolor.GetName(), &changecolor },
        { begindraw.GetName(), &begindraw },
        { enddraw.GetName(), &enddraw },
        { addvertex.GetName(), &addvertex },
        { setfillmode.GetName(), &setfillmode },
        { setviewport.GetName(), &setviewport },
        { showviewport.GetName(), &showviewport },
        { setclipping.GetName(), &setclipping },
	};
public:
	static void InvokeScript(const string& s, const vector<string>& params);
    static void Initialize();
    static void ShutDown();
};
































































