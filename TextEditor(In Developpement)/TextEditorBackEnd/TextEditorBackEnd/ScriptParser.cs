﻿using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TextEditorBackEnd
{   
    public struct Error
    {
        int errorLine;
        string errorMessage;

        public int ErrorLine { get => errorLine;  }
        public Error(ref int errorLine, ref string errorMessage)
        {
            this.errorLine = errorLine;
            this.errorMessage = errorMessage;
        }

        public override string ToString()
        {
            return "Error on Line: " + errorLine.ToString() + ' ' + errorMessage + '\n';
        }

        public override int GetHashCode()
        {
            return errorLine;
        }
    }

    public static class ScriptParser
    {
        //Impletement Base Script Syntax Detection
        static Dictionary<string, List<List<string>>> commands = new Dictionary<string, List<List<string>>>();
        static HashSet<Error> flaggedLines = new HashSet<Error>();
        static List<string> errorlessContents = new List<string>();
        static HashSet<string> variables = new HashSet<string>();
        readonly static HashSet<string> colors = new HashSet<string> { "LIGHTGRAY",
                                                                    "GRAY",
                                                                    "DARKGRAY",
                                                                    "YELLOW",
                                                                    "GOLD",
                                                                    "ORANGE",
                                                                    "PINK",
                                                                    "RED",
                                                                    "MAROON",
                                                                    "GREEN",
                                                                    "LIME",
                                                                    "DARKGREEN",
                                                                    "SKYBLUE",
                                                                    "BLUE",
                                                                    "DARKBLUE",
                                                                    "PURPLE",
                                                                    "VIOLET",
                                                                    "DARKPURPLE",
                                                                    "BEIGE",
                                                                    "BROWN",
                                                                    "DARKBROWN",
                                                                    "WHITE",
                                                                    "BLACK",
                                                                    "BLANK",
                                                                    "MAGENTA",
                                                                    "RAYWHITE", };
        public static HashSet<Error> Errors { get => flaggedLines; }
        public static List<string> ErrorlessContents { get => errorlessContents; }


        static int lineNumber = 0;
        public static void LoadCommands(string filepath)
        {
            var temp = FileManager.LoadFile(filepath).ToHashSet();            
            foreach (var str in temp)
            {
                int bracketIndex = str.LastIndexOf('(');
                var name = str.Remove(bracketIndex);               
                if (!commands.ContainsKey(name)) commands.Add(name, new List<List<string>>());
                commands[name].Add(new List<string>(str.Substring(bracketIndex + 1, str.Length - bracketIndex - 2).Split(',', StringSplitOptions.TrimEntries)));
            }
        }

        public static bool CheckForErrors(ref string contents)
        {
            var array = contents.Split('\n').ToList();
            return CheckForErrors(ref array);
        }
        public static bool CheckForErrors(ref List<string> array)
        {
            errorlessContents.Clear();
            flaggedLines.Clear();
            variables.Clear();
            lineNumber = 0;
            bool init = false, toggle = false;
            if (array.Count == 0) return true;
            if (!array[0].StartsWith("Init"))
            {
                AddError("Script Must Start With Init Command");
                return false;
            }
            foreach (var arg in array)
            {
                ++lineNumber;
                string line = arg.Replace("\r", string.Empty);
                if (string.IsNullOrWhiteSpace(line)) continue;
                int bracketIndex = line.LastIndexOf('(');
                if (line.StartsWith("//")) continue;
                if (bracketIndex == -1)
                {
                    var parameters = GetParams(line, ' ');
                    if (line.StartsWith("float")) CheckFloat(ref line, ref parameters);
                    else if (line.StartsWith("int")) CheckInt(ref line, ref parameters);
                    else if (line.Contains('='))
                        CheckArithemticErrors(ref line);
                    else AddError("Invalid Line Argument - No Variable Declaration Or Valid Command Found");
                }
                else
                {
                    var commandName = line.Remove(bracketIndex);
                    if (commands.ContainsKey(commandName))
                    {
                        int index = line.LastIndexOf(')');
                        if (index == -1) AddError("Invalid Command Declaration: Missing Ending Parantheses");                    
                        if (line.Remove(0, commandName.Length)[0] != '(') AddError("Invalid Command Declaration: Parentheses must follow Immediately After Command Name");
                        if (line.Length <= index + 1 && !string.IsNullOrWhiteSpace(line.Substring(index + 1))) AddError("Invalid Command Declaration: Closing Paranthese Must Be That Last Character");
                        var parameters = GetParams(line.Substring(bracketIndex + 1).Replace(")", String.Empty), ',');
                        switch (commandName)
                        {
                            case "Init":
                                if (init) AddError("Only One Init Command Allowed");
                                else init = true;
                                break;
                            case "ToggleGrid":
                                if (toggle) AddError("Only One Toggle Grid Command Allowed");
                                else toggle = true;
                                break;
                        }

                        bool validAmount = false;
                        int idx = 0;
                        for (; idx < commands[commandName].Count; idx++)
                        {
                            if (commands[commandName][idx] == null) continue;
                            if (commands[commandName][idx].Count == parameters.Length) validAmount = true;
                            if (validAmount) break;
                        }
                        if (!validAmount)
                        {
                            AddError($"Command {commandName} Does Not Take {parameters.Length} Overloads");
                            continue;
                        }
                        for(int i = 0; i < parameters.Length; i++)
                        {
                            float rF;
                            int rI;
                            switch (commands[commandName][idx][i])
                            {   
                                case "int":
                                    if (!int.TryParse(parameters[i], out rI)) AddError($"Parameter {i + 1} of command {commandName} takes in tpye: Int");
                                    break;
                                case "float":
                                    if (float.TryParse(parameters[i], out rF)) AddError($"Parameter {i + 1} of command {commandName} takes in tpye: Float");
                                    break;
                                case "bool":
                                    if (parameters[i] != "true" && parameters[i] != "false") AddError($"Parameter {i + 1} of command {commandName} takes in tpye: Bool");
                                    break;
                                case "color":
                                    if (!float.TryParse(parameters[i], out rF) && !variables.Contains(parameters[i]))
                                    {
                                        if (!colors.Contains(parameters[i])) AddError($"Parameter {i + 1} of command {commandName} takes in type: Color");
                                    }
                                    else if (parameters.Length <= i + 2) AddError($"Parameters {i + 1} - {i + 3} of command {commandName} must make up a valid RGB Color");
                                    else
                                    {
                                        ++i;
                                        if (!float.TryParse(parameters[i], out rF) && !variables.Contains(parameters[i])) 
                                            AddError($"Parameters {i} - {i + 2} of command {commandName} must make up a valid RGB Color");
                                        ++i;
                                        if (!float.TryParse(parameters[i], out rF) && !variables.Contains(parameters[i]))
                                            AddError($"Parameters {i - 1} - {i + 1} of command {commandName} must make up a valid RGB Color");
                                    }
                                    break;
                                case "vector3":
                                    if (parameters.Length <= i + 2) AddError($"Parameters {i + 1} - {i + 3} of command {commandName} must make up a valid Vector3");
                                    for (int j = i; i < j + 2; i++)
                                        if (!float.TryParse(parameters[i], out rF))
                                            AddError($"Parameters {i + 1} - {i + 3} of command {commandName} must make up a valid Vector3");
                                    break;
                                case "vector2":
                                    if (parameters.Length <= i + 1) AddError($"Parameters {i + 1} & {i + 2} of command {commandName} must make up a valid Vector2");
                                    if (!float.TryParse(parameters[i], out rF)) AddError($"Parameters {i + 1} & {i + 2} of command {commandName} must make up a valid Vector2");
                                    ++i;
                                    if (!float.TryParse(parameters[i], out rF)) AddError($"Parameters {i} & {i + 1} of command {commandName} must make up a valid Vector2");
                                    break;
                            }
                        }
                    }
                    else if (line.Contains('=')) CheckArithemticErrors(ref line);
                }
            }
            return flaggedLines.Count == 0;
        }

        public static void SaveValidScript(string filepath, string contents)
        {
            CheckForErrors(ref contents);
            FileManager.SaveFile(ref errorlessContents, filepath);
        }

        static void AddError(string errorMsg)
        {
            flaggedLines.Add(new Error(ref lineNumber, ref errorMsg));
        }

        static void CheckFloat(ref string line, ref string[] paramerters)
        {
            if (line.Length < 11 || paramerters.Length < 4 || line[5] != ' ')
            {
                AddError("Float Declaration Incomplete: Example Format - \"float x = 0\"");
                return;
            }

            float result;
            if (paramerters[2].Length != 1) AddError("Invalid Float Declaration: Equal Sign Should Be Seperated By Spaces");
            else if (paramerters[2][0] != '=') AddError("Invalid Float Declaration: Equal Sign Should Follow Variable Name");
            else if (!variables.Add(paramerters[1])) AddError($"Float Redifinition: Float - {paramerters[1]} Already Defined");
            else if (!float.TryParse(paramerters.Last(), out result)) AddError("Invalid Left hand Value: Valid Formats - 0, 0f, 0.0f");
            else errorlessContents.Add(line);
        }
        
        static void CheckInt(ref string line, ref string[] paramerters)
        {
            if (line.Length < 12 || paramerters.Length < 4 || line[5] != ' ')
            {
                AddError("Float Declaration Incomplete: Example Format - \"float x = 0\"");
                return;
            }

            int result;
            if (paramerters[2].Length != 1) AddError("Invalid Float Declaration: Equal Sign Should Be Seperated By Spaces");
            else if (paramerters[2][0] != '=') AddError("Invalid Float Declaration: Equal Sign Should Follow Variable Name");
            else if (!variables.Add(paramerters[1])) AddError($"Float Redifinition: Float - {paramerters[1]} Already Defined");
            else if (!int.TryParse(paramerters.Last(), out result)) AddError("Invalid Left hand Value");
            else errorlessContents.Add(line);
        }

        

       
        static void CheckArithemticErrors(ref string line) 
        {
            var parameters = GetParams(line, ' ');
            if (parameters.Length < 3) AddError("Invalid Mathematical Equation: Ex. Variblename operator value/mathematical expression -> x = 5 + 2/ x += 5");
            else if (!variables.Contains(parameters[0])) AddError("Invalid Mathematical Expression: Left Value must be a declared variable");
            else
            {
                bool Operator = true;
                short equals = 0;
                foreach (var p in parameters)
                {
                    float result;
                    if (p.Contains('='))
                    {
                        ++equals;
                        if (Operator)
                        {
                            AddError("Invalid Mathematical Statement: Operators Must Follow A Number Or Variable");
                            return;
                        }
                        Operator = true;
                        if (equals > 1)
                        {
                            AddError("Invalid Mathematical Statement: Only One Assignment Operator Allowed Per Statement");
                            return;
                        }
                    }
                    else if (isOperator(p))
                    {
                        if (Operator)
                        {
                            AddError("Invalid Mathematical Statement: Operators Must Follow A Number Or Variable");
                            return;
                        }
                        Operator = true;
                    }
                    else if (variables.Contains(p) || float.TryParse(p, out result))
                    {
                        if (!Operator)
                        {
                            AddError("Invalid Mathematical Statement: Numbers/Variables Must Follow An Operator");
                            return;
                        }
                        Operator = false;
                    }
                    else
                    {
                        AddError("Invalid Mathematical Statement: Expressions Must Only Contain Operators, Numbers or Variables");
                        return;
                    }
                }
            }
        }

        static bool isOperator(string str)
        {
            switch (str[0])
            {
                case '+':
                case '-':
                case '*':
                case '/':
                    return true;
            }
            return false;
        }

        static string[] GetParams(string line, char delemeter)
        {
            return line.Split(delemeter, StringSplitOptions.RemoveEmptyEntries);
        }
    }
}