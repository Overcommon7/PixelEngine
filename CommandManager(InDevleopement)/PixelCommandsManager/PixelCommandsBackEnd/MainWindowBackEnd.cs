using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using Windows.ApplicationModel.Background;
using Windows.UI.Composition;
using Windows.UI.Popups;

namespace PixelCommandsBackEnd
{
    public static class MainWindowBackEnd
    {
        public static Dictionary<string, List<string>> commands = new Dictionary<string, List<string>>();
        public static void LoadCommands(string filepath)
        {
            commands.Clear();
            FileManager.LoadFile(filepath).ToHashSet();
            var temp = FileManager.LoadFile(filepath).ToHashSet();
            foreach (var str in temp)
            {
                int bracketIndex = str.LastIndexOf('(');
                string name = str;
                if (bracketIndex != -1)
                    name = str.Remove(bracketIndex);

                if (!commands.ContainsKey(name))
                    commands.Add(name, new List<string>());
                if (bracketIndex != -1) commands[name].Add(str.Substring(bracketIndex));
            }
        }

        public static void RemoveCommand(string commandName)
        {
            EditWindowBackEnd.RemoveCommandFromScriptMap(commandName);
            EditWindowBackEnd.RemoveCommandFromVCSProj(commandName);
        }
    }
}
