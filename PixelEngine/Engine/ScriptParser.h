#pragma once
#include "Defines.h"
#include "PixelFloat.h"

struct Command
{
    string funcitonName;
    vector<string> params;
};

class ScriptParser
{
    static bool IsDigit(const string& str);
    static bool IsFloat(const string& str);
    static void LoadFloat(const string& line, unordered_map<string, PixelFloat>& variables);
    static void LoadCommand(string line, unordered_map<string, PixelFloat>& variables);
    static void InternalFloatCommand(string line, unordered_map<string, PixelFloat>& variables);
    static float GetTotal(const string& line, unordered_map<string, PixelFloat>& variables, const vector<string>& params);
    static void ArithmeticFloatCommand(const string& line, unordered_map<string, PixelFloat>& variables);
    static void SetFloatCommand(const string& line, unordered_map<string, PixelFloat>& variables);
    static bool Arithmetic(const char& c, float& total, const float& value);


    static vector<string> GetParams(const string& line);
    static inline vector<Command> commands = {};
    static inline int lineNumber = 0;
    static inline int printStatemets = 0;
public:
    ScriptParser() = delete;
    ScriptParser(const ScriptParser& s) = delete;
    ScriptParser& operator=(const ScriptParser& s) = delete;

    static vector<Command> ParseText(const vector<string>& instructions, unordered_map<string, PixelFloat>& variables);
};

