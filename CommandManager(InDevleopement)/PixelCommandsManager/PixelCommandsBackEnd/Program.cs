using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace PixelCommandsBackEnd
{
    public static class Enums
    {
        static public Dictionary<string, List<string>> enums = new Dictionary<string, List<string>>();

        static public void Save(string filepath)
        {
            if (File.Exists(filepath)) File.Delete(filepath);
            using (var fs = File.Create(filepath))
            {
                using (var sw = new StreamWriter(fs))
                {
                    foreach (var item in enums)
                    {
                        sw.WriteLine(item.Key);
                        foreach (var value in item.Value)
                        {
                            sw.WriteLine(value);
                        }
                        sw.Write("SEndLine\n");
                    }
                }
            }
        }

        static public void Load(string filepath)
        {
            string key = string.Empty;
            enums.Clear();
            using (var fs = new FileStream(filepath, FileMode.OpenOrCreate))
            {
                using (var sr = new StreamReader(fs))
                {
                    while (!sr.EndOfStream)
                    {
                        key = sr.ReadLine();
                        enums.Add(key, new List<string>());
                        string value = sr.ReadLine();
                        while (value != "SEndLine")
                        {
                            enums[key].Add(value);
                            value = sr.ReadLine();
                        }
                    }
                }
            }
        }
    }

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
            if (delemeters == null) delemeters = new char[1] { '\n' };
            var listedContents = contents.Split(delemeters).ToList();
            SaveFile(ref listedContents, filepath);
            
        }

        public static bool CheckForFileInDirectory(string directory, string filename)
        {
            foreach (var file in Directory.GetFiles(directory))
                if (file == filename) return true;
            return false;
        }
    }
}
