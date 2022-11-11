using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PixelCommandsBackEnd
{
    public static class EditWindowBackEnd
    {
        #region FilePaths
        public static readonly string ScriptMapFilePath =
#if DEBUG
            Directory.GetParent(Directory.GetCurrentDirectory()).Parent.Parent.Parent.FullName + '\\' +
#else
            Directory.GetCurrentDirectory() + '\\' +
#endif
            "ScriptMap.h";

        public static readonly string ProjectFilePath =
#if DEBUG
        Directory.GetParent(Directory.GetCurrentDirectory()).Parent.Parent.Parent.FullName + '\\' +
#else
        Directory.GetCurrentDirectory() + '\\' +
#endif
        "PixelEngine.vcxproj";

        public static readonly string CommandDirectory =
#if DEBUG
        Directory.GetParent(Directory.GetCurrentDirectory()).Parent.Parent.Parent.FullName +
#else
        Directory.GetCurrentDirectory() +
#endif
        "\\UserCommands\\";
        #endregion

        public static string UserCommandDirectory { get => CommandDirectory; }
        static string GetDefaultCommandContents(string commandName)
        {
            string contents = "#include \"pch.h\"\n#include \"Commands.h\"\n#include \"Utilities.h\"\n\n";
            contents += "class " + commandName.ToUpper() + " : public Commands\n";
            contents += "{\npublic:\n";
            contents += "    " + commandName.ToUpper() + "() {}\n";
            contents += "    //Returns The Name Of The Function\n";
            contents += "    string GetName() const override { return \"" + commandName + "\"; }\n\n";
            contents += "    //Invoke Gets Called When A PixelScript Calls The Name Of The Fuction\n";
            contents += "    void Invoke(const vector<string>& params) const override\n";
            return contents;
        }

        static void CreateCommandTemplate(string commandName, string commandPath)
        {
            var contents = GetDefaultCommandContents(commandName) + "    {\n\n    }\n};";

            using (var fs = File.Create(commandPath))
            {
                using (var sw = new StreamWriter(fs))
                {
                    sw.Write(contents);
                }
            }
        }

        static void CreateNewCommand(string commandPath, string commandName, string oldPath)
        {
            var contents = GetDefaultCommandContents(commandName);
            var file = File.ReadAllLines(oldPath);
            bool commence = false;
            for (int i = 0; i < file.Length; i++)
            {
                if (commence) contents += file[i] + "\n";
                else if (file[i].Contains("vector<string>")) commence = true;
            }

            using (var fs = File.Create(commandPath))
            {
                using (var sw = new StreamWriter(fs))
                {
                    sw.Write(contents);
                }
            }
        }

        private static void AppendToScriptMap(string commandName)
        {
            var lines = new List<string>();
            var temp = File.ReadAllLines(ScriptMapFilePath);
            for (int i = 0; i < temp.Length; i++)
            {
                if (temp[i] == "	};")
                {
                    lines.Add("        { " + commandName.ToLower() + ".GetName(), &" + commandName.ToLower() + " },");
                }
                lines.Add(temp[i]);
                if (temp[i] == "private:")
                {
                    lines.Add("    inline static const " + commandName.ToUpper() + ' ' + commandName.ToLower() + " = {};");
                }
                if (temp[i] == "#pragma once")
                {
                    lines.Add("#include \"UserCommands/" + commandName + ".h\"");
                }
            }
            FileManager.SaveFile(ref lines, ScriptMapFilePath);
        }

        public static void RemoveCommandFromScriptMap(string commandName)
        {
            var contents = File.ReadAllLines(ScriptMapFilePath);
            List<string> lines = new List<string>();
            var upper = "const " + commandName.ToUpper() + " ";
            var lower = commandName.ToLower() + ".GetName()";
            for (int i = 0; i < contents.Length; i++)
            {
                if (contents[i].Contains(commandName + ".h")) continue;
                else if (contents[i].Contains(upper)) continue;
                else if (contents[i].Contains(lower)) continue;
                lines.Add(contents[i]);
            }
            FileManager.SaveFile(ref lines, ScriptMapFilePath);
        }

        public static void RemoveCommandFromVCSProj(string commandName)
        {
            AppendToVCXProjFile(null, commandName);
        }

#nullable enable
        private static void AppendToVCXProjFile(string? commandName = null, string? oldname = null)
        {
            var lines = new List<string>();
            var contents = File.ReadAllLines(ProjectFilePath);
            bool remove = !string.IsNullOrEmpty(oldname);
            bool added = false;
            bool insertLine = !string.IsNullOrEmpty(commandName);
            for (int i = 0; i < contents.Length; i++)
            {
                if (!added && insertLine && contents[i].Contains("=\"pch.h"))
                {
                    lines.Add("     <ClInclude Include=\"UserCommands\\" + commandName + ".h" + "\" />");
                    added = true;
                }
                    
                if (remove && contents[i].Contains(oldname))
                {
                    remove = false;
                    continue;
                }
                lines.Add(contents[i]);
            }
            FileManager.SaveFile(ref lines, ProjectFilePath);
        }
#nullable disable

        public static string GetCommandName(string line)
        {
            int bracketIndex = line.LastIndexOf('(');
            string name = line;
            if (bracketIndex != -1)
                name = line.Remove(bracketIndex);
            return name;
        }
        public static bool AddCommandToEngine(string commandName, bool replace = false)
        {
            var commandPath = Path.Combine(CommandDirectory, commandName + ".h");
            if (!replace && FileManager.CheckForFileInDirectory(CommandDirectory, commandPath)) return false;
            if (replace && File.Exists(commandPath)) File.Delete(commandPath);

            CreateCommandTemplate(commandName, commandPath);
            AppendToScriptMap(commandName);
            AppendToVCXProjFile(commandName);
            return true;
        }

        public static void EditCommand(string oldname, string newName)
        {
            var commandPath = Path.Combine(CommandDirectory, newName + ".h");
            var oldPath = Path.Combine(CommandDirectory, oldname + ".h");

            CreateNewCommand(commandPath, newName, oldPath);
            AppendToScriptMap(newName);
            AppendToVCXProjFile(newName);
        }

        
    }
}
