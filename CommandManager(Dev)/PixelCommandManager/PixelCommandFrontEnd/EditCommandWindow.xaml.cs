using PixelCommandsBackEnd;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;

namespace PixelCommandFrontEnd
{
    /// <summary>
    /// Interaction logic for EditCommandWindow.xaml
    /// </summary>
    public partial class EditCommandWindow : Window
    {
        readonly string oldName = string.Empty;
        readonly bool add = false;
        public EditCommandWindow(string name, List<string> param)
        {
            InitializeComponent();
            Title = "Edit Command Window";
            Load(ref param);
            wpf_CommandName.Text = name;            
            oldName = name;
        }

        public EditCommandWindow()
        {
            InitializeComponent();
            Title = "Add Command Window";
            var list = new List<string>();
            Load(ref list);
            wpf_CommandName.Text = "NewCommand";
            oldName = string.Empty;
            add = true;
        }

        private void Wpf_CommandName_MouseLeave(object sender, MouseEventArgs e)
        {
            if (string.IsNullOrEmpty(wpf_CommandName.Text))
                wpf_CommandName.Text = "NewCommand";
            wpf_CommandName.Text= wpf_CommandName.Text.Replace(" ", "_");
        }

        void Load(ref List<string> param)
        {
            wpf_CommandName.MouseLeave += Wpf_CommandName_MouseLeave;
            wpf_AppliedParameters.Items.Clear();
            foreach (var p in param)
                wpf_AppliedParameters.Items.Add(p.ToLower());
            wpf_ParamterType.Items.Clear();
            wpf_ParamterType.Items.Add("Float");
            wpf_ParamterType.Items.Add("Int");
            wpf_ParamterType.Items.Add("Bool");
            wpf_ParamterType.Items.Add("Color");
            foreach (var e in Enums.enums)
            {
                var name = e.Key;
                var c = char.ToUpper(name[0]);
                if (name.Length > 1) name = c + name.Substring(1);
                wpf_ParamterType.Items.Add(name); ;
            }                
            wpf_ParamterType.SelectedItem = wpf_ParamterType.Items[0];
        }

        private void wpf_Add_Click(object sender, RoutedEventArgs e)
        {
            if (wpf_ParamterType.SelectedItem == null) return;
            wpf_NewParameters.Items.Add(wpf_ParamterType.SelectedItem.ToString());  
        }

        private void wpf_CommandName_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (string.IsNullOrEmpty(wpf_CommandName.Text)) return;
            if (!char.IsLetter(wpf_CommandName.Text[0])) wpf_CommandName.Text = string.Empty;
            else if (!char.IsLetterOrDigit(wpf_CommandName.Text.Last())) 
                wpf_CommandName.Text = wpf_CommandName.Text.Substring(0, wpf_CommandName.Text.Length - 1);
        }

        private void wpf_NewParamsRemove_Click(object sender, RoutedEventArgs e)
        {
            if (wpf_NewParameters.SelectedItem == null) return;
            wpf_NewParameters.Items.RemoveAt(wpf_NewParameters.SelectedIndex);
        }

        private void wpf_Apply_Click(object sender, RoutedEventArgs e)
        {
            string result = "(";
            for (int i = 0; i < wpf_NewParameters.Items.Count - 1; i++)
                result += wpf_NewParameters.Items[i].ToString() + ", ";
            result += wpf_NewParameters.Items[wpf_NewParameters.Items.Count - 1].ToString() + ')';

            foreach (var str in wpf_AppliedParameters.Items)
                if (str.ToString() == result) return;

            wpf_AppliedParameters.Items.Add(result.ToLower());
        }

        private void wpf_ParamsRemove_Click(object sender, RoutedEventArgs e)
        {
            if (wpf_AppliedParameters.SelectedItem == null) return;
            wpf_AppliedParameters.Items.RemoveAt(wpf_AppliedParameters.SelectedIndex);
        }

        private void wpf_Save_Click(object sender, RoutedEventArgs e)
        {
            var contents = FileManager.LoadFile(MainWindow.CommandFilePath);
            var upper = oldName.ToUpper();
            if (!add)
            {
                for (int i = 0; i < contents.Count;)
                {
                    if (upper == EditWindowBackEnd.GetCommandName(contents[i]).ToUpper())
                        contents.RemoveAt(i);
                    else i++;
                }
            }
            
            var hs = new SortedSet<string>(contents);
            if (wpf_AppliedParameters.Items.Count == 0) hs.Add(wpf_CommandName.Text);
            else foreach (var item in wpf_AppliedParameters.Items)
                    hs.Add(wpf_CommandName.Text + item.ToString());

            if (add)
            {
                bool replace = false;
                while (true)
                {
                    if (EditWindowBackEnd.AddCommandToEngine(wpf_CommandName.Text, replace))
                    {
                        contents = new List<string>(hs);
                        FileManager.SaveFile(ref contents, MainWindow.CommandFilePath);
                        Close();
                        return;
                    }
                    if (MessageBox.Show("Command Already Exists! Replace?", "Command Cmanager", MessageBoxButton.YesNo, MessageBoxImage.Exclamation) == MessageBoxResult.Yes)
                        replace = true;
                    else
                    {
                        Close();
                        return;
                    }
                } 
            }
            else
            {
                EditWindowBackEnd.EditCommand(oldName, wpf_CommandName.Text);
                contents = new List<string>(hs);
                FileManager.SaveFile(ref contents, MainWindow.CommandFilePath);
                MainWindow.RemoveCommand(oldName, sender, e);
            }
            Close();
            return;
        }
    }
}
