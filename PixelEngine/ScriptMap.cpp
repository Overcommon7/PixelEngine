#include "pch.h"
#include "ScriptMap.h"
#include "Commands.h"

void ScriptMap::InvokeScript(const string& s, const vector<string>& params)
{
	if (scripts.contains(s))
		scripts.at(s)->Invoke(params);
}

void ScriptMap::Initialize()
{
	if (!textEditorOpened && launchTextEditor) system("start ..\\TextEditor\\TextEditorFrontEnd.exe");
	textEditorOpened = true;
}

void ScriptMap::ShutDown()
{

}
