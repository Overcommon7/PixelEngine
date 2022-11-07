using System;
using System.Collections.Generic;
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
        static HashSet<string> commands = new HashSet<string>();
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
            commands = FileManager.LoadFile(filepath).ToHashSet();
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
                    if (commands.Contains(commandName))
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
                                else if (CheckInit(ref parameters))
                                {
                                    errorlessContents.Add(line);
                                    init = true;
                                }
                                break;
                            case "DrawPixel":
                                if (CheckDrawPixel(ref parameters))
                                    errorlessContents.Add(line);
                                break;
                            case "ToggleGrid":
                                if (toggle) AddError("Only One Toggle Grid Command Allowed");
                                else if (CheckToggleGrid(ref parameters))
                                {
                                    errorlessContents.Add(line);
                                    toggle = true;
                                }
                                break;
                            case "ChangeColor":
                                if (CheckChangeColor(ref parameters))
                                    errorlessContents.Add(line);
                                break;
                            default:
                                errorlessContents.Add(line);
                                break;
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

        static bool CheckInit(ref string[] parameters)
        {

            if (parameters.Length != 3)
            {
                AddError("Init Fucntion Takes Three Arguments");
                return false;
            }
            foreach (var p in parameters)
            {
                if (variables.Contains(p)) continue;
                int result;
                if (int.TryParse(p, out result)) continue;
                AddError("Init Command Arguments Must Be Of Type: Int");
                return false;
            }
            return true;
        }

        static bool CheckDrawPixel(ref string[] parameters)                                
        {
            if (parameters.Length != 2)
            {
                AddError("Draw Pixel Command Takes Two Interger Argumnets");
                return false;
            }
            foreach (var p in parameters)
            {
                if (variables.Contains(p)) continue;
                int result;
                if (int.TryParse(p, out result)) continue;
                AddError("Init Command Arguments Must Be Of Type: Int");
                return false;
            }
            return true;

        }

        static bool CheckChangeColor(ref string[] parameters)
        {
            if (parameters.Length == 1 && !colors.Contains(parameters[0].ToUpper()))
            {
                AddError("Invalid Color Passed: See Utils::Colors for a complete list of Colors");
                return false;
            }

            foreach (var p in parameters)
            {
                if (variables.Contains(p)) continue;
                float result;
                if (float.TryParse(p, out result))
                {
                    if (result < 0f || result > 255f) return false;
                    continue;
                }
                AddError("Init Command Arguments Must Be Of Type: Int");
                return false;
            }
            return true;
        }

        static bool CheckToggleGrid(ref string[] parameters)
        {
            if (parameters.Length != 1) AddError("Toggle Grid Only Takes One Argument");
            else if (parameters[0].ToLower() == "true" || parameters[0].ToLower() == "false") return true;
            else AddError("Invalid Argumnet Passed: Toggle Grid Command");
            return false;
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
