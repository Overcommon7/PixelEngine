using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using TextEditorBackEnd;

namespace TextEditorFrontEnd
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public string filepath = string.Empty;
        public readonly string commandFilePath = Directory.GetParent(Directory.GetCurrentDirectory()).ToString() + "\\PixelEngine\\TextEditorCommands.txt";
        bool saved = true;
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
            ScriptParser.LoadCommands(commandFilePath);
            Deactivated += MainWindow_LostFocus;
            Closing += MainWindow_Closed;
        }

        List<string> GetFormattedString(string contents)
        {
            contents = contents.Replace("\r\n", "\n");
            contents = contents.Replace("\r", "\n");
            return contents.Split('\n').ToList();
        }

        private void MainWindow_Closed(object? sender, EventArgs e)
        {
            if (saved) return;
            if (MessageBox.Show("Save the File?", "Script Editor", MessageBoxButton.YesNo, MessageBoxImage.Warning) != MessageBoxResult.Yes) return;
            var contents = GetFormattedString(TextField.Text);
            FileManager.SaveFile(ref contents, filepath);
        }

        private void MainWindow_LostFocus(object? sender, EventArgs e)
        {
            Compilie_Click(null, null);
            ScriptParser.SaveValidScript(filepath, TextField.Text);
        }

        void AddLine(object sender, RoutedEventArgs e)
        {
            if (!TextField.IsFocused) return;

            int temp = TextField.SelectionStart;
            TextField.Text = TextField.Text.Insert(temp, "\n");
            TextField.SelectionStart = temp + 1; 
        }
        private void TextBox_TextChanged(object sender, TextChangedEventArgs e)
        {



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

            string message = "File Contains Scripting Errors\nSave Without Errors?";
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
                    ScriptParser.SaveValidScript(filepath, TextField.Text);
                    break;
                case MessageBoxResult.No:
                    var contents = GetFormattedString(TextField.Text);
                    FileManager.SaveFile(ref contents, filepath);
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
    }
}
