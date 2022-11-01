using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace TextEditorBackEnd
{
    public static class FileManager
    {
        public static List<string> LoadFile(string filepath)
        {
            if (!File.Exists(filepath)) return new List<string>();
            return File.ReadAllLines(filepath).ToList();
        }

        public static string LoadFileAsSingleString(string filepath)
        {
            if (!File.Exists(filepath)) return string.Empty;
            return File.ReadAllText(filepath);
        }

        public static void SaveFile(ref List<string> contents, string filepath)
        {
            if (string.IsNullOrEmpty(filepath)) return;
            if (contents.Count == 0) return;
            if (File.Exists(filepath)) File.Delete(filepath);
            using (var fs = File.Create(filepath))
            {
                using (var sw = new StreamWriter(fs))
                {
                    for (int i = 0; i < contents.Count - 1; i++)
                        sw.WriteLine(contents[i]);
                    sw.Write(contents.Last());        
                }
            }
        }
        public static void SaveFile(ref string contents, string filepath, char[] delemeters = null)
        {
            if (string.IsNullOrEmpty(filepath)) return;
            if (string.IsNullOrEmpty(contents)) return;
            if (delemeters == null) delemeters = new char[1] {'\n'};
            var listedContents = contents.Split(delemeters).ToList();
            SaveFile(ref listedContents, filepath);
        }
    }
}
