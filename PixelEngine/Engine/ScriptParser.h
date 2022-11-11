#pragma once
#include "Defines.h"
#include "PixelFloat.h"

struct Command
{
    string funcitonName;
    vector<string> params;
};

enum class OperationType
{
    Null,
    PlusEquals,
    MinusEquals,
    MultiplyEquals,
    DivideEquals
};

class ScriptParser
{
    static void LoadFloat(const string& line, unordered_map<string, PixelFloat>& variables);
    static void LoadCommand(string line, unordered_map<string, PixelFloat>& variables);
    static void InternalFloatCommand(const string& line, unordered_map<string, PixelFloat>& variables, const OperationType& type);
    static float GetTotal(const string& line, unordered_map<string, PixelFloat>& variables, const vector<string>& params, const bool& skipCheck = false, const bool& skipCheck2 = false);
    static void ArithmeticFloatCommand(const string& line, unordered_map<string, PixelFloat>& variables);
    static void SetFloatCommand(const string& line, unordered_map<string, PixelFloat>& variables);
    static bool Arithmetic(const char& c, float& total, const float& value);
    static void Print(const Command& command);

    static vector<string> GetParams(const string& line);
    static inline vector<Command> commands = {};
    static inline int lineNumber = 0;
    static inline int printStatemets = 0;
    static inline stringstream ss = {};
public:
    ScriptParser() = delete;
    ScriptParser(const ScriptParser& s) = delete;
    ScriptParser& operator=(const ScriptParser& s) = delete;

    static vector<Command> ParseText(const vector<string>& instructions, unordered_map<string, PixelFloat>& variables);
};

