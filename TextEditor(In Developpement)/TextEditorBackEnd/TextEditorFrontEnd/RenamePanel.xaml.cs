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

namespace TextEditorFrontEnd
{
    /// <summary>
    /// Interaction logic for RenamePanel.xaml
    /// </summary>
    public partial class RenamePanel : Window
    {
        public RenamePanel()
        {
            InitializeComponent();
        }

        private void RepaceOne_Click(object sender, RoutedEventArgs e)
        {
            int idx = MainWindow.Instance.TextField.Text.IndexOf(FindText.Text);
            if (idx == -1) return;

            MainWindow.Instance.TextField.Text = MainWindow.Instance.TextField.Text.Insert(idx + FindText.Text.Length, ReplaceText.Text);
            MainWindow.Instance.TextField.Text = MainWindow.Instance.TextField.Text.Remove(idx, FindText.Text.Length);
        }

        private void RepaceAll_Click(object sender, RoutedEventArgs e)
        {
            if (MainWindow.Instance.TextField.Text.IndexOf(FindText.Text) == -1) return;
            MainWindow.Instance.TextField.Text = MainWindow.Instance.TextField.Text.Replace(FindText.Text, ReplaceText.Text);
        }
    }
}
