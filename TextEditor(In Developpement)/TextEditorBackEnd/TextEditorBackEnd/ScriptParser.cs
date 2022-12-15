using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;

namespace TextEditorBackEnd
{
    public class Enums
    {
        public Dictionary<string, List<string>> enums = new Dictionary<string, List<string>>();
        public Dictionary<string, bool> bools = new Dictionary<string, bool>();

        public void Load(string filepath)
        {
            string key = string.Empty;
            enums.Clear();
            bools.Clear();
            using (var fs = new FileStream(filepath, FileMode.OpenOrCreate))
            {
                using (var sr = new StreamReader(fs))
                {
                    while (!sr.EndOfStream)
                    {
                        key = sr.ReadLine();
                        if (string.IsNullOrEmpty(key)) continue;
                        enums.Add(key, new List<string>());
                        bools.Add(key, false);
                        string value = sr.ReadLine();
                        while (value != "SEndLine" && !sr.EndOfStream)
                        {
                            enums[key].Add(value);
                            value = sr.ReadLine();
                        }
                    }
                }
            }
        }

        public void ResetBools()
        {
            foreach (var element in bools)
                bools[element.Key] = false;
        }
    }
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
            return errorLine + errorMessage.GetHashCode();
        }

        public static explicit operator Error(string str)
        {
            var temp = str.Replace("Error on Line: ", string.Empty);
            int line = int.Parse(temp.Substring(0, temp.IndexOf(' ')));
            var error = temp.Replace("\n", string.Empty);
            error = error.Replace(line.ToString() + ' ', string.Empty);
            return new Error(ref line, ref error);
        }
    }

    public static class ScriptParser
    {
        static Dictionary<string, List<List<string>>> commands = new Dictionary<string, List<List<string>>>();
        static Dictionary<string, List<List<string>>> lowerCommands = new Dictionary<string, List<List<string>>>();
        static HashSet<Error> flaggedLines = new HashSet<Error>();
        static List<string> errorlessContents = new List<string>();
        static HashSet<string> variables = new HashSet<string>();
        static Enums enums = new Enums();
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
            commands = new Dictionary<string, List<List<string>>>();
            lowerCommands = new Dictionary<string, List<List<string>>>();
            var temp = FileManager.LoadFile(filepath).ToHashSet();            
            foreach (var str in temp)
            {
                int bracketIndex = str.LastIndexOf('(');
                string name = str;
                if (bracketIndex != -1)
                    name = str.Remove(bracketIndex);

                if (!commands.ContainsKey(name)) 
                    commands.Add(name, new List<List<string>>());
                if (bracketIndex == -1) commands[name].Add(new List<string>());
                else commands[name].Add(new List<string>(str.Substring(bracketIndex + 1, str.Length - bracketIndex - 2).Split(',', StringSplitOptions.TrimEntries)));
            }

            foreach (var command in commands)
                lowerCommands.Add(command.Key.ToLower(), command.Value);

        }

        public static void LoadEnums(string filepath)
        {
            enums.Load(filepath);
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
            char[] operators = new char[] { '*', '+', '/', '-' };
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
                if (string.IsNullOrWhiteSpace(line))
                {
                    errorlessContents.Add("\n");
                    continue;
                }
                if (line.StartsWith("//"))
                {
                    errorlessContents.Add(line);
                    continue;
                }
                int bracketIndex = line.LastIndexOf('(');
                
                if (bracketIndex == -1)
                {
                    var parameters = GetParams(line, ' ');
                    if (line.StartsWith("float")) CheckFloat(ref line, ref parameters);
                    else if (line.StartsWith("int")) CheckInt(ref line, ref parameters);
                    else if (line.Contains('=') && CheckArithemticErrors(ref line)) errorlessContents.Add(line);
                    else AddError("Invalid Line Argument - No Variable Declaration Or Valid Command Found");
                }
                else
                {
                    var commandName = line.Remove(bracketIndex);
                    int errorCount = flaggedLines.Count;
                    if (commands.ContainsKey(commandName))
                    {
                        int index = line.LastIndexOf(')');
                        if (index == -1) AddError("Invalid Command Declaration: Missing Ending Parantheses");
                        if (line.Remove(0, commandName.Length)[0] != '(') AddError("Invalid Command Declaration: Parentheses must follow Immediately After Command Name");
                        if (line.Length <= index + 1 && !string.IsNullOrWhiteSpace(line.Substring(index + 1))) AddError("Invalid Command Declaration: Closing Paranthese Must Be That Last Character");
                        var parameters = GetParams(line.Substring(bracketIndex + 1).Replace(")", string.Empty), ',');
                        for (int j = 0; j < parameters.Length; j++)
                        {
                            if (parameters[j].Length >= 2 && parameters[j].IndexOfAny(operators, 1) == -1)
                                parameters[j] = parameters[j].Replace(" ", string.Empty);
                        }

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
                            case "Print":
                                continue;
                            default:
                                break;
                        }

                        bool validAmount = false;
                        int idx = 0;
                        for (; idx < commands[commandName].Count; idx++)
                        {
                            if (commands[commandName][idx] == null) continue;
                            if (commands[commandName][idx].Count == parameters.Length) validAmount = true;
                            if (validAmount) 
                                break;
                        }
                        if (!validAmount)
                        {
                            AddError($"Command {commandName} Does Not Take {parameters.Length} Overloads");
                            continue;
                        }

                        
                        for (int i = 0; i < parameters.Length; i++)
                        {
                            if (commands[commandName][idx][i] == "string") continue;
                            int k = -1;
                            if (parameters[i].Length >= 2)
                                k = parameters[i].IndexOfAny(operators, 1);
                            if (k != -1)
                            {
                                int temp = flaggedLines.Count;
                                var before = parameters[i];
                                parameters[i] = parameters[i].Insert(k + 1, "=");
                                CheckArithemticErrors(ref parameters[i]);
                                if (temp == flaggedLines.Count)
                                {
                                    line = line.Replace(before, parameters[i].Replace("=", string.Empty));
                                    parameters[i] = "1";   
                                }
                            }


                            float rF;
                            int rI;
                            switch (commands[commandName][idx][i])
                            {
                                case "int":
                                    if (variables.Contains(parameters[i])) break;
                                    if (!int.TryParse(parameters[i], out rI)) AddError($"Parameter {i + 1} of command {commandName} takes in tpye: Int");
                                    break;
                                case "float":
                                    if (variables.Contains(parameters[i])) break;
                                    if (!float.TryParse(parameters[i], out rF)) AddError($"Parameter {i + 1} of command {commandName} takes in tpye: Float");
                                    break;
                                case "bool":
                                    if (parameters[i].ToLower() != "true" && parameters[i].ToLower() != "false") AddError($"Parameter {i + 1} of command {commandName} takes in tpye: Bool");
                                    break;
                                case "color":
                                    if (!colors.Contains(parameters[i].ToUpper())) AddError($"Parameter {i + 1} of command {commandName} takes in type: Color");
                                    break;
                                case "string":
                                    break;
                                default:
                                    if (enums.enums.ContainsKey(commands[commandName][idx][i]))
                                    {
                                        if (!enums.enums[commands[commandName][idx][i]].Contains(parameters[i].ToLower()))
                                            AddError($"Paramer {i + 1} of command {commandName} takes in type Enum: {commands[commandName][idx][i]}");
                                    }
                                    else AddError($"Unknown Parameter Type - Name: {parameters[i]}");
                                    break;
                            }
                        }
                        if (errorCount == flaggedLines.Count)
                            errorlessContents.Add(line);
                    }
                    else if (line.Contains('=') && CheckArithemticErrors(ref line)) errorlessContents.Add(line);
                    else AddError("Command Does Not Exist!");
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

        static void AddSpace(ref string line)
        {
            List<int> indexes = new List<int>();
            for (int i = 0; i < line.Length; i++)
            {
                string temp = string.Empty + line[i];
                if (string.IsNullOrWhiteSpace(temp)) continue;
                if (temp.Contains('=') && i + 1 < line.Length && isOperator(string.Empty + line[i + 1]))
                {
                    ++i;
                    indexes.Add(i + 1);   
                }
                else if (temp.Contains('=') || isOperator(temp)) indexes.Add(i + 1);
                else if (char.IsLetter(temp[0]))
                {
                    while (i < line.Length && !isOperator(string.Empty + line[i]) && line[i] != '=')
                        ++i;
                    indexes.Add(i);
                }
            }           
            for (int i = 0; i < indexes.Count; i++)
                line = line.Insert(indexes[i] + i, " ");
            line = line.Replace("  ", " ");
        }
        static bool CheckArithemticErrors(ref string line) 
        {
            AddSpace(ref line);
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
                            return false;
                        }
                        Operator = true;
                        if (equals > 1)
                        {
                            AddError("Invalid Mathematical Statement: Only One Assignment Operator Allowed Per Statement");
                            return false;
                        }
                    }
                    else if (isOperator(p))
                    {
                        if (Operator)
                        {
                            AddError("Invalid Mathematical Statement: Operators Must Follow A Number Or Variable");
                            return false;
                        }
                        Operator = true;
                    }
                    else if (variables.Contains(p) || float.TryParse(p, out result))
                    {
                        if (!Operator)
                        {
                            AddError("Invalid Mathematical Statement: Numbers/Variables Must Follow An Operator");
                            return false;
                        }
                        Operator = false;
                    }
                    else
                    {
                        AddError("Invalid Mathematical Statement: Expressions Must Only Contain Operators, Numbers or Variables");
                        return false;
                    }
                }
                return true;
            }
            return false;
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
            var entries = line.Split(delemeter, StringSplitOptions.TrimEntries);
            List<string> result = new List<string>();
            foreach (var entry in entries)
                if (!string.IsNullOrEmpty(entry) && !string.IsNullOrWhiteSpace(entry))
                    result.Add(entry);
            return result.ToArray(); 
        }


        public static List<string> GetVariables(List<string> text)
        {
            List<string> result = new List<string>();
            foreach (var line in text)
            {
                if (string.IsNullOrEmpty(line)) continue;
                int idx = line.IndexOf(' ');
                if (idx == -1) continue;
                var p = line.Substring(0, idx).ToLower();
                if (p != "float" && p != "int") continue;
                var par = GetParams(line, ' ');
                if (par.Length < 4) continue;
                result.Add(par[1]);
            }
            return result;
        }

        struct Suggestion
        {
            public int weight;
            public string text;

            public Suggestion(int weight, string text)
            {
                this.weight = weight;
                this.text = text;
            }

            public static int Comapre(Suggestion left, Suggestion right)
            {
                if (left.weight == right.weight)
                    return left.text.CompareTo(right.text);
                return right.weight.CompareTo(left.weight);
            }
        }

      

        public static List<string> GetSuggestions(string line, ref List<string> vars)
        {
            List<string> suggestions = new List<string>();
            line = line.Replace("\r\n", "");
            line = line.Replace("\n", "");
            line = line.Replace("\t", "");
            if (!line.Contains("("))
            {
                var lowerLine = line.ToLower();
                HashSet<int> indexes = new HashSet<int>();
                int i = 0;
                foreach (var command in lowerCommands)
                {

                    if (string.IsNullOrWhiteSpace(line) || command.Key.Contains(lowerLine))
                        indexes.Add(i);
                    i++;
                }
                i = 0;
                foreach (var command in commands)
                {
                    if (indexes.Contains(i))
                        suggestions.Add(command.Key);
                    i++;
                }
            }
            else
            {
                bool variablesAdded = false;
                bool boolAdded = false;
                var name = line.Substring(0, line.IndexOf('(')).ToLower();
                enums.ResetBools();
                if (!lowerCommands.ContainsKey(name)) return suggestions;
                int j = 0;
                for (int i = 0; i < line.Length; i++)
                    if (line[i] == ',') j++;

                foreach (var paramList in lowerCommands[name])
                {
                    if (j >= paramList.Count) continue;
                    var listItem = paramList[j].ToLower();
                    if (listItem == "int" || listItem == "float")
                    {
                        if (variablesAdded) continue;
                        foreach (var v in vars)
                            suggestions.Add(v);
                        variablesAdded = true;
                    }
                    else if (listItem == "bool")
                    {
                        if (boolAdded) continue;
                        suggestions.Add("true");
                        suggestions.Add("false");
                    }
                    else
                    {
                        if (enums.bools[paramList[j]]) continue;
                        foreach (var type in enums.enums[paramList[j]])
                            suggestions.Add(type); 
                    }        
                }
            }

            if (!string.IsNullOrEmpty(line))
            {
                List<Suggestion> temp = new List<Suggestion>();
                foreach (var s in suggestions)
                {
                    int i = 0;
                    string com = string.Empty + line[i];

                    while (s.StartsWith(com) && i < line.Length)
                    {
                        com += line[i];
                        i++;
                    }
                    temp.Add(new Suggestion(i, s));
                }

                temp.Sort(Suggestion.Comapre);
                suggestions.Clear();
                foreach (var s in temp)
                    suggestions.Add(s.text);
            }
            return suggestions;
        }
    }

    
}
