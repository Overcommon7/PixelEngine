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
	if (fs::exists(file))
		fs::remove(file);
	ofstream create(file);
	create.close();
	fstream inFile(file);
	for (const auto& commmand : scripts)
		inFile << commmand.first << '\n';
	inFile << "Print\n";
	inFile.close();

	if (!textEditorOpened) system("start ..\\TextEditor\\TextEditorFrontEnd.exe");
	textEditorOpened = true;
}

void ScriptMap::ShutDown()
{
	if (fs::exists(file))
		fs::remove(file);
}
