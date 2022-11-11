#pragma once
#include "UserCommands/SetFOV.h"
#include "UserCommands/SetFarPlane.h"
#include "UserCommands/SetNearPlane.h"
#include "UserCommands/SetCameraDirection.h"
#include "UserCommands/SetCameraPosition.h"
#include "UserCommands/PopMatrix.h"
#include "UserCommands/PushScaling.h"
#include "UserCommands/PushRotationZ.h"
#include "UserCommands/PushRotationY.h"
#include "UserCommands/PushRotationX.h"
#include "UserCommands/PushTranslation.h"
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
    inline static const SETFOV setfov = {};
    inline static const SETFARPLANE setfarplane = {};
    inline static const SETNEARPLANE setnearplane = {};
    inline static const SETCAMERADIRECTION setcameradirection = {};
    inline static const SETCAMERAPOSITION setcameraposition = {};
    inline static const POPMATRIX popmatrix = {};
    inline static const PUSHSCALING pushscaling = {};
    inline static const PUSHROTATIONZ pushrotationz = {};
    inline static const PUSHROTATIONY pushrotationy = {};
    inline static const PUSHROTATIONX pushrotationx = {};
    inline static const PUSHTRANSLATION pushtranslation = {};
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
    inline static bool textEditorOpened = false;
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
        { pushtranslation.GetName(), &pushtranslation },
        { pushrotationx.GetName(), &pushrotationx },
        { pushrotationy.GetName(), &pushrotationy },
        { pushrotationz.GetName(), &pushrotationz },
        { pushscaling.GetName(), &pushscaling },
        { popmatrix.GetName(), &popmatrix },
        { setcameraposition.GetName(), &setcameraposition },
        { setcameradirection.GetName(), &setcameradirection },
        { setnearplane.GetName(), &setnearplane },
        { setfarplane.GetName(), &setfarplane },
        { setfov.GetName(), &setfov },
	};
public:
	static void InvokeScript(const string& s, const vector<string>& params);
    static void Initialize();
    static void ShutDown();
};

















































