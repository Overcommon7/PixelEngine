#pragma once
#include "UserCommands/TestCmd.h"
#include "UserCommands/TestCmd.h"
#include "UserCommands/TestCmd.h"
#include "UserCommands/AddModel.h"
#include "UserCommands/ChangePixelColor.h"
#include "UserCommands/PopMatrix.h"
#include "UserCommands/Vertex.h"
#include "UserCommands/SetFOV.h"
#include "UserCommands/SetFarPlane.h"
#include "UserCommands/SetNearPlane.h"
#include "UserCommands/SetCameraDirection.h"
#include "UserCommands/SetCameraPosition.h"
#include "UserCommands/PushScaling.h"
#include "UserCommands/PushRotationZ.h"
#include "UserCommands/PushRotationY.h"
#include "UserCommands/PushTranslation.h"
#include "UserCommands/SetClipping.h"
#include "UserCommands/ShowViewport.h"
#include "UserCommands/SetViewport.h"
#include "UserCommands/SetFillMode.h"
#include "UserCommands/EndDraw.h"
#include "DrawPixel.h"
#include "ToggleGrid.h"
#include "Init.h"
#include "Commands.h"

class ScriptMap
{
private:
    inline static const TESTCMD testcmd = {};
    inline static const TESTCMD testcmd = {};
    inline static const TESTCMD testcmd = {};
    inline static const ADDMODEL addmodel = {};
    inline static const CHANGEPIXELCOLOR changepixelcolor = {};
    inline static const POPMATRIX popmatrix = {};
    inline static const VERTEX vertex = {};
    inline static const SETFOV setfov = {};
    inline static const SETFARPLANE setfarplane = {};
    inline static const SETNEARPLANE setnearplane = {};
    inline static const SETCAMERADIRECTION setcameradirection = {};
    inline static const SETCAMERAPOSITION setcameraposition = {};
    inline static const PUSHSCALING pushscaling = {};
    inline static const PUSHROTATIONZ pushrotationz = {};
    inline static const PUSHROTATIONY pushrotationy = {};
    inline static const PUSHTRANSLATION pushtranslation = {};
    inline static const SETCLIPPING setclipping = {};
    inline static const SHOWVIEWPORT showviewport = {};
    inline static const SETVIEWPORT setviewport = {};
    inline static const SETFILLMODE setfillmode = {};
    inline static const ENDDRAW enddraw = {};
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
        { enddraw.GetName(), &enddraw },
        { setfillmode.GetName(), &setfillmode },
        { setviewport.GetName(), &setviewport },
        { showviewport.GetName(), &showviewport },
        { setclipping.GetName(), &setclipping },
        { pushtranslation.GetName(), &pushtranslation },
        { pushrotationy.GetName(), &pushrotationy },
        { pushrotationz.GetName(), &pushrotationz },
        { pushscaling.GetName(), &pushscaling },
        { setcameraposition.GetName(), &setcameraposition },
        { setcameradirection.GetName(), &setcameradirection },
        { setnearplane.GetName(), &setnearplane },
        { setfarplane.GetName(), &setfarplane },
        { setfov.GetName(), &setfov },
        { vertex.GetName(), &vertex },
        { popmatrix.GetName(), &popmatrix },
        { changepixelcolor.GetName(), &changepixelcolor },
        { addmodel.GetName(), &addmodel },
        { testcmd.GetName(), &testcmd },
        { testcmd.GetName(), &testcmd },
        { testcmd.GetName(), &testcmd },
	};
public:
	static void InvokeScript(const string& s, const vector<string>& params);
    static void Initialize();
    static void ShutDown();
};

















