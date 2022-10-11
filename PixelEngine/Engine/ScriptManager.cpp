#include "pch.h"
#include "ScriptManager.h"
#include "Commands.h"
#include "ScriptMap.h"


void ScriptManager::LoadScript(const string& script)
{
	system("cls");
	scriptFilePath = filepath + script;
	scriptName = script;
	fstream inFile(scriptFilePath);
	vector<string> lines;
	string line;
	while (!inFile.eof())
	{
		std::getline(inFile, line);
		lines.push_back(line);
	}
	inFile.close();
	commands = ScriptParser::ParseText(lines, variables);
}

void ScriptManager::Update()
{
	if (User::GetKey() == KEY_F5)
		LoadScript(scriptName);
	for (auto& var : variables)
		var.second.ResetCurrentValue();
}

void ScriptManager::RunScripts()
{
	for (const auto& c : commands)
		ScriptMap::InvokeScript(c.funcitonName, c.params);
}
