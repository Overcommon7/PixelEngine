#include "pch.h"
#include "ScriptMap.h"
#include "Commands.h"
#include "Defines.h"

void ScriptMap::InvokeScript(const string& s, const vector<string>& params)
{
	if (scripts.contains(s))
		scripts.at(s)->Invoke(params);
}

void ScriptMap::Initialize()
{
	if (!launchTextEditor) return;
	string command("start ");
	command += workingDirectory.substr(0, workingDirectory.find_last_of('/'));
	command = command.substr(0, command.find_last_of('/'));
	command += "/TextEditor.exe";
	for (auto& c : command)
		if (c == '/') c = '\\';
	system(command.c_str());

}

void ScriptMap::ShutDown()
{

}
