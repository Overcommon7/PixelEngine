#pragma once
#include "ScriptParser.h"
#include "User.h"

class ScriptManager
{
    inline static vector<Command> commands = {};
    inline static unordered_map<string, PixelFloat> variables = {};
    inline static string scriptFilePath = {};
    inline static string scriptName = {};
public:
    ScriptManager() = delete;
    ScriptManager(const ScriptManager& s) = delete;
    ScriptManager& operator=(const ScriptManager& s) = delete;

    static void LoadScript(const string& script);
    static void Update();
    static void RunScripts();
};