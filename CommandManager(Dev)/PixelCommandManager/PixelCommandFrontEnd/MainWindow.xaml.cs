using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using PixelCommandsBackEnd;

namespace PixelCommandFrontEnd
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        static readonly string commandFilePath =
#if DEBUG
            Directory.GetParent(Directory.GetCurrentDirectory()).Parent.Parent.Parent.FullName + '\\' +
#else
            Directory.GetCurrentDirectory() + "\\PixelEngine\\" +
#endif
            "TextEditorCommands.txt";
       
        List<string> allEnums = new List<string>();
        List<string> allCommands = new List<string>();
        static public string CommandFilePath { get => commandFilePath; }

        public MainWindow()
        {
            InitializeComponent();
            MainWindowBackEnd.LoadCommands(commandFilePath);
            Enums.Load();
            Loaded += MainWindow_Loaded;
            Closing += MainWindow_Closing;
        }

        private void MainWindow_Closing(object? sender, EventArgs e)
        {
            Loaded -= MainWindow_Loaded;
            Closing -= MainWindow_Closing;
        }

        private void MainWindow_Loaded(object sender, RoutedEventArgs e)
        {
            wpf_CommandList.Items.Clear();
            wpf_CommandViwer.Items.Clear();
            wpf_EnumList.Items.Clear();
            wpf_EnumViewer.Items.Clear();
            allCommands.Clear();
            allEnums.Clear();
 
            foreach (var item in MainWindowBackEnd.commands)
                allCommands.Add(item.Key);
            allCommands.Sort();
            foreach (var item in allCommands)
                wpf_CommandList.Items.Add(item);
           
            foreach (var item in Enums.enums)
                allEnums.Add(item.Key);
            allEnums.Sort();
            foreach (var item in allEnums)
                wpf_EnumList.Items.Add(item);       
        }



        private void wpf_AddCommand_Click(object sender, RoutedEventArgs e)
        {
            EditCommandWindow edit = new EditCommandWindow();
            edit.ShowDialog();
            MainWindowBackEnd.LoadCommands(commandFilePath);
            MainWindow_Loaded(sender, e);
        }

        private void wpf_SearchCommand_TextChanged(object sender, TextChangedEventArgs e)
        {
            wpf_CommandList.Items.Clear();
            wpf_CommandViwer.Items.Clear();
            if (string.IsNullOrEmpty(wpf_SearchCommand.Text))
            {            
                foreach (var item in allCommands)
                    wpf_CommandList.Items.Add(item);
                return;
            }
            foreach (var str in allCommands)
            {
                if (string.IsNullOrEmpty(str)) continue;
                if (!str.StartsWith(wpf_SearchCommand.Text)) continue;
                wpf_CommandList.Items.Add(str);
            }    
        }

        private void wpf_SearchEnum_TextChanged(object sender, TextChangedEventArgs e)
        {
            wpf_EnumList.Items.Clear();
            wpf_EnumViewer.Items.Clear(); 
            if (string.IsNullOrEmpty(wpf_SearchEnum.Text))
            {
                foreach (var item in allEnums)
                    wpf_EnumList.Items.Add(item);
                return;
            }
            foreach (var str in allEnums)
            {
                if (string.IsNullOrEmpty(str)) continue;
                if (!str.StartsWith(wpf_SearchEnum.Text)) continue;
                wpf_EnumList.Items.Add(str);
            }
        }

        private void wpf_EditCommand_Click(object sender, RoutedEventArgs e)
        {
            if (wpf_CommandList.SelectedItem == null) return;
            EditCommandWindow editWindow = new EditCommandWindow(wpf_CommandList.SelectedItem.ToString(), MainWindowBackEnd.commands[wpf_CommandList.SelectedItem.ToString()]);
            editWindow.ShowDialog();
            MainWindowBackEnd.LoadCommands(commandFilePath);
            MainWindow_Loaded(sender, e);
        }

        private void wpf_CommandList_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (wpf_CommandList.SelectedItem == null) return;
            wpf_CommandViwer.Items.Clear();
            var name = wpf_CommandList.SelectedItem.ToString();
            foreach (var parameters in MainWindowBackEnd.commands[name])
                wpf_CommandViwer.Items.Add(parameters);
            switch (name)
            {
                case "Init":
                case "ToggleGrid":
                case "DrawPixel":
                case "Print":
                    wpf_EditCommand.IsEnabled = false;
                    wpf_DeleteCommand.IsEnabled = false;
                    break;
                default:
                    wpf_EditCommand.IsEnabled = true;
                    wpf_DeleteCommand.IsEnabled = true;
                    break;
            }
        }

        private void wpf_EnumList_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (wpf_EnumList.SelectedItem == null) return;
            wpf_EnumViewer.Items.Clear();
            var name = wpf_EnumList.SelectedItem.ToString();
            foreach (var types in Enums.enums[name])
                wpf_EnumViewer.Items.Add(types);
        }

        private void wpf_CommandViwer_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            wpf_CommandViwer.UnselectAll();
        }

        private void wpf_EnumViewer_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            wpf_EnumViewer.UnselectAll();
        }

        private void wpf_EditEnum_Click(object sender, RoutedEventArgs e)
        {
            if (wpf_EnumList.SelectedItem == null) return;
            EditEnums edit = new EditEnums(wpf_EnumList.SelectedItem.ToString());
            edit.ShowDialog();
            MainWindow_Loaded(sender, e);
        }

        static public void RemoveCommand(string commandName, object sender, RoutedEventArgs e)
        {
            MainWindowBackEnd.RemoveCommand(commandName);
            var contents = File.ReadAllLines(CommandFilePath);
            var upper = commandName.ToUpper();
            List<string> list = new List<string>();
            for (int i = 0; i < contents.Length; i++)
                if (EditWindowBackEnd.GetCommandName(contents[i]).ToUpper() == upper)
                    continue;
                else list.Add(contents[i]);
            FileManager.SaveFile(ref list, CommandFilePath);
            var path = System.IO.Path.Combine(EditWindowBackEnd.CommandDirectory, commandName + ".h");
            if (File.Exists(path)) File.Delete(path);
        }

        public void wpf_DeleteCommand_Click(object sender, RoutedEventArgs e)
        {
            if (wpf_CommandList.SelectedItem == null) return;
            RemoveCommand(wpf_CommandList.SelectedItem.ToString(), sender, e);
            MainWindowBackEnd.LoadCommands(commandFilePath);
            MainWindow_Loaded(sender, e);
        }

        private void wpf_AddEnum_Click(object sender, RoutedEventArgs e)
        {
            EditEnums edit = new EditEnums();
            edit.ShowDialog();
            MainWindow_Loaded(sender, e);
        }

        private void wpf_DeleteEnum_Click(object sender, RoutedEventArgs e)
        {
            if (wpf_EnumList.SelectedItem == null) return;
            Enums.RemoveEnum(wpf_EnumList.SelectedItem.ToString());
            MainWindow_Loaded(sender, e);
        }
    }
}
