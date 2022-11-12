using PixelCommandsBackEnd;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace PixelCommandFrontEnd
{
    /// <summary>
    /// Interaction logic for EditEnums.xaml
    /// </summary>
    public partial class EditEnums : Window
    {
        string oldName = string.Empty;
        bool edit = false;
        public EditEnums(string name)
        {
            InitializeComponent();
            oldName = name;
            edit = true;
            Loaded += EditEnums_Loaded;
            Closed += EditEnums_Closed;
        }

        public EditEnums()
        {
            InitializeComponent();
            Loaded += EditEnums_Loaded;
            Closed += EditEnums_Closed;
        }

        private void EditEnums_Closed(object? sender, EventArgs e)
        {
            Closed -= EditEnums_Closed;
            Loaded -= EditEnums_Loaded;
        }

        private void EditEnums_Loaded(object sender, RoutedEventArgs e)
        {
            wpf_Enumerations.Items.Clear();
            if (edit)
            {
                foreach (var item in Enums.GetValueFromKey(oldName))
                    wpf_Enumerations.Items.Add(item);
                wpf_EnumName.Text = oldName;
            }
                
            else
                wpf_EnumName.Text = "NewEnum";

        }

        private void wpf_AddEnum_Click(object sender, RoutedEventArgs e)
        {
            if (string.IsNullOrEmpty(wpf_NewEnumeration.Text)) return;
            wpf_Enumerations.Items.Add(wpf_NewEnumeration.Text);
            wpf_NewEnumeration.Focus();
            wpf_NewEnumeration.SelectAll();
        }

        private void wpf_RemoveEnum_Click(object sender, RoutedEventArgs e)
        {
            if (wpf_Enumerations.SelectedItem == null) return;
            wpf_Enumerations.Items.Remove(wpf_Enumerations.SelectedItem);
        }

        private void wpf_Save_Click(object sender, RoutedEventArgs e)
        {
            if (string.IsNullOrEmpty(wpf_EnumName.Text))
            {
                MessageBox.Show("Enum Name Can't Be Empty", "Command Manager", MessageBoxButton.OK);
                return;
            }
            if (edit) Enums.RemoveEnum(oldName);
            List<string> list = new List<string>();
            foreach (var item in wpf_Enumerations.Items)
                list.Add(item.ToString());
            if (!Enums.AddEnum(wpf_EnumName.Text, ref list) && !edit)
            {
                if (MessageBoxResult.No == MessageBox.Show("Enum Already Exists! Alter Exisiting?", "Command Manager", MessageBoxButton.YesNo)) return;
                edit = true;
                wpf_Save_Click(sender, e); 
                return;
            }
            Enums.Save();
            Enums.Load();
            Close();
        }
    }
}
