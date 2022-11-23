using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using TextEditorBackEnd;
using static System.Net.Mime.MediaTypeNames;

namespace TextEditorFrontEnd
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public string filepath = string.Empty;
        public readonly string commandFilePath =
#if DEBUG
            Directory.GetParent(Directory.GetCurrentDirectory()).Parent.Parent.Parent.FullName + '\\' +
#else
            Directory.GetCurrentDirectory() + '\\' +
#endif
            "TextEditorCommands.txt"; 

        public readonly string enumsFilePath =
#if DEBUG
          Directory.GetParent(Directory.GetCurrentDirectory()).Parent.Parent.Parent.FullName + '\\' +
#else
          Directory.GetCurrentDirectory() + '\\' +
#endif
          "TextEditorEnums.txt";

        bool saved = true;
        bool saveOnExit = false;
        bool saveFullFile = false;

        readonly string Float = "float";
        readonly string Int = "int";
        List<string> variables = new List<string>();
        public virtual int ItemHeight { get; set; }
        public MainWindow()
        {
            InitializeComponent();
            RoutedCommand save = new RoutedCommand();
            save.InputGestures.Add(new KeyGesture(Key.S, ModifierKeys.Control));
            CommandBindings.Add(new CommandBinding(save, Save_Click));
            RoutedCommand load = new RoutedCommand();
            load.InputGestures.Add(new KeyGesture(Key.O, ModifierKeys.Control));
            CommandBindings.Add(new CommandBinding(load, Open_Click));
            RoutedCommand compile = new RoutedCommand();
            compile.InputGestures.Add(new KeyGesture(Key.B, ModifierKeys.Control));
            CommandBindings.Add(new CommandBinding(compile, Compilie_Click));
            TextField.AcceptsReturn = true;
            TextField.AcceptsTab = true;
            TextField.Focusable = false;
            TextField.IsEnabled = false;
            TextField.HorizontalScrollBarVisibility = ScrollBarVisibility.Auto;
            TextField.VerticalScrollBarVisibility = ScrollBarVisibility.Auto;
            ErrorList.MaxHeight = 400;
            ErrorList.MaxWidth = 1000;
            SuggestionBox.Items.Clear();
            SuggestionBox.MouseDoubleClick += SuggestionBox_MouseDoubleClick;
            TextField.LostFocus += TextField_LostFocus;
            TextField.GotFocus += TextField_GotFocus;
            ScriptParser.LoadCommands(commandFilePath);
            ScriptParser.LoadEnums(enumsFilePath);
            Deactivated += MainWindow_LostFocus;
            Closing += MainWindow_Closing;
            Closed += MainWindow_Closed;
        }

        private void SuggestionBox_MouseDoubleClick(object sender, MouseButtonEventArgs e)
        {
            if (SuggestionBox.SelectedItem == null) return;
            var value = SuggestionBox.SelectedItem.ToString();
            if (string.IsNullOrEmpty(value)) return;
             SuggestionBox.UnselectAll();
            SuggestionBox.ReleaseMouseCapture();
            TextField.Focus();
            var lineIdx = TextField.GetLineIndexFromCharacterIndex(TextField.SelectionStart);
            var line = TextField.GetLineText(lineIdx);
            var bracketIdx = line.IndexOf('(');
            if (string.IsNullOrEmpty(line) || string.IsNullOrWhiteSpace(line))
            {
                int idx = TextField.Text.IndexOf(line);
                TextField.Text = TextField.Text.Insert(idx + 1, "\n" + value);
                TextField.SelectionStart = idx + value.Length + 1;
            }
            else if (bracketIdx != -1)
            {
                int currentIdx = TextField.SelectionStart;
                while (TextField.Text[currentIdx] != ',' && TextField.Text[currentIdx] != '(')
                    currentIdx--;

                TextField.Text = TextField.Text.Insert(currentIdx + 1, value);
                TextField.SelectionStart = currentIdx + 1 + value.Length;
            }
            else
            {
                int idx = TextField.GetCharacterIndexFromLineIndex(lineIdx);
                TextField.Text = TextField.Text.Remove(idx, line.Length - 1);
                TextField.Text = TextField.Text.Insert(idx, value);
                TextField.SelectionStart = idx + value.Length;
            }
        }

        private void FillSuggestionBox()
        {
            var line = TextField.GetLineText(TextField.GetLineIndexFromCharacterIndex(TextField.SelectionStart));
            foreach (var suggestion in ScriptParser.GetSuggestions(line, ref variables))
                SuggestionBox.Items.Add(suggestion);
        }
        private void TextField_GotFocus(object sender, RoutedEventArgs e)
        {
            SuggestionBox.Items.Clear();
            FillSuggestionBox();
        }

        private void TextField_LostFocus(object sender, RoutedEventArgs e)
        {
            SuggestionBox.Items.Clear();
        }

        private void MainWindow_Closed(object? sender, EventArgs e)
        {
            Deactivated -= MainWindow_Closed;
            Closing -= MainWindow_Closing;
            Closed -= MainWindow_Closed;
            TextField.LostFocus -= TextField_LostFocus;

            if (!saveFullFile && !saveOnExit) return;

            var contents = GetFormattedString(TextField.Text);
            FileManager.SaveFile(ref contents, filepath);
        }

        List<string> GetFormattedString(string contents)
        {
            contents = contents.Replace("\r\n", "\n");
            contents = contents.Replace("\r", "\n");
            return contents.Split('\n').ToList();
        }

        private void MainWindow_Closing(object? sender, EventArgs e)
        {
            if (saved) return;
            saveOnExit = MessageBox.Show("Save the File?", "Script Editor", MessageBoxButton.YesNo, MessageBoxImage.Warning) == MessageBoxResult.Yes;           
        }

        private void MainWindow_LostFocus(object? sender, EventArgs e)
        {
            if (saved) return;
            Compilie_Click(null, null);
            ScriptParser.SaveValidScript(filepath, TextField.Text);
        }

        //void AddLine(object sender, RoutedEventArgs e)
        //{
        //    if (!TextField.IsFocused) return;

        //    int temp = TextField.SelectionStart;
        //    TextField.Text = TextField.Text.Insert(temp, "\n");
        //    TextField.SelectionStart = temp + 1; 
        //}
        private void TextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            var tb = (TextBox)sender;
            bool tab = false;
            int offset = 0, addedLength = 0;
            using (tb.DeclareChangeBlock())
            {
                foreach (var c in e.Changes)
                {
                    if (c.AddedLength == 0) continue;
                    offset = c.Offset;
                    addedLength = c.AddedLength;
                    var text = tb.Text.Substring(offset, addedLength);
                    tab = text.Contains('\t');
                    if (text.Contains('\n'))
                    {
                        variables = ScriptParser.GetVariables(GetFormattedString(TextField.Text));
                        break;
                    }
                    if (tab) break;
                }
            }
            SuggestionBox.Items.Clear();
            FillSuggestionBox();
            if (tab && SuggestionBox.Items.Count > 0)
            {
                int idx = TextField.SelectionStart;
                TextField.Select(offset, addedLength);
                TextField.SelectedText = TextField.SelectedText.Replace("\t", "");
                //TextField.SelectionStart = idx;
                SuggestionBox.SelectedItem = SuggestionBox.Items[0];
                SuggestionBox_MouseDoubleClick(sender, null);
            }
               
            if (string.IsNullOrEmpty(Title) || Title.EndsWith('*')) return;
            saved = false;
            Title += "*";
        }

        private void Open_Click(object sender, RoutedEventArgs e)
        {
            Microsoft.Win32.OpenFileDialog dlg = new Microsoft.Win32.OpenFileDialog();
            dlg.DefaultExt = ".txt"; // Default file extension
            dlg.Filter = "Text documents (.txt)|*.txt"; // Filter files by extension

            // Show save file dialog box
            Nullable<bool> result = dlg.ShowDialog();

            // Process save file dialog box results
            if (result == true)
            {
                MainWindow_Closing(sender, e);
                MainWindow_Closed(sender, e);
                filepath = dlg.FileName;
                TextField.Text = FileManager.LoadFileAsSingleString(filepath);
                ErrorList.Items.Clear();
                Title = "Script Editor - " + Path.GetFileName(filepath);
                saved = true;
                TextField.Focusable = true;
                TextField.IsEnabled = true;

            }
            
        }

        MessageBoxResult SaveWithErrors()
        {
            if (ScriptParser.Errors.Count == 0) return MessageBoxResult.OK;

            string message = "File Contains Scripting Errors\nSave With Errors?";
            string caption = "Text Editor";
            return MessageBox.Show(message, caption, MessageBoxButton.YesNoCancel, MessageBoxImage.Warning);
        }

        private void Save_Click(object sender, RoutedEventArgs e)
        {
            Compilie_Click(sender, e);
            switch (SaveWithErrors())
            {
                case MessageBoxResult.None:
                case MessageBoxResult.Cancel:
                    return;
                case MessageBoxResult.Yes:
                case MessageBoxResult.OK:
                    var contents = GetFormattedString(TextField.Text);
                    FileManager.SaveFile(ref contents, filepath);
                    saveFullFile = true;
                    break;
                case MessageBoxResult.No:
                    ScriptParser.SaveValidScript(filepath, TextField.Text);
                    saveFullFile = false;
                    break;
            }

            ErrorList.Items.Clear();
            foreach (var error in ScriptParser.Errors)
                ErrorList.Items.Add(error.ToString());
            Title = "Script Editor - " + Path.GetFileName(filepath);
            saved = true;
        }

        private void Save_As_Click(object sender, RoutedEventArgs e)
        {
            string name = Path.GetFileNameWithoutExtension(filepath) + "_Copy";
            int copyNumber = 0;
            while (File.Exists(name + copyNumber.ToString() + ".txt"))
                ++copyNumber;
            if (copyNumber != 0)
                name = name + copyNumber.ToString();

            Microsoft.Win32.SaveFileDialog dlg = new Microsoft.Win32.SaveFileDialog();
            dlg.FileName = name; // Default file name
            dlg.DefaultExt = ".txt"; // Default file extension
            dlg.Filter = "Text documents (.txt)|*.txt"; // Filter files by extension

            // Show save file dialog box
            Nullable<bool> result = dlg.ShowDialog();

            // Process save file dialog box results
            if (result == true)
            {
                Compilie_Click(sender, e);
                File.Copy(filepath, dlg.FileName, true);
                filepath = dlg.FileName;
                switch (SaveWithErrors())
                {
                    case MessageBoxResult.None:
                    case MessageBoxResult.Cancel:
                        return;
                    case MessageBoxResult.Yes:
                    case MessageBoxResult.OK:
                        ScriptParser.SaveValidScript(filepath, TextField.Text);
                        break;
                    case MessageBoxResult.No:
                        var contents = GetFormattedString(TextField.Text);
                        FileManager.SaveFile(ref contents, filepath);
                        break;
                }
                ErrorList.Items.Clear();
                Title = "Script Editor - " + Path.GetFileName(filepath);
                saved = true;
            }    
        }
        private void Compilie_Click(object sender, RoutedEventArgs e)
        {
            string contents = TextField.Text;
            ScriptParser.LoadCommands(commandFilePath);
            ScriptParser.LoadEnums(enumsFilePath);
            if (ScriptParser.CheckForErrors(ref contents))
            {
                ErrorList.Items.Clear();
                ErrorList.Items.Add("No Complilation Errors");
            }
            else
            {
                ErrorList.Items.Clear();
                foreach (var error in ScriptParser.Errors)
                    ErrorList.Items.Add(error.ToString());
            }               
        }

        private void ErrorList_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (ErrorList.SelectedItem == null) return;
            var str = ErrorList.SelectedItem.ToString();
            if (string.IsNullOrEmpty(str)) return;
            if (!str.StartsWith("Error on Line: "))
            {
                ErrorList.UnselectAll();
                return;
            }
            Error err;
            ScriptParser.Errors.TryGetValue((Error)str, out err);
            if (err.ErrorLine == 0) return;
            var text = TextField.GetLineText(err.ErrorLine - 1);
            ErrorList.UnselectAll();
            ErrorList.ReleaseMouseCapture();
            TextField.Focus();
            TextField.Select(TextField.Text.IndexOf(text), text.Length - 2);    
        }
    }
}
