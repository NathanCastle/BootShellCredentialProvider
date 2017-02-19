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
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Configurator
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        List<ConfigModel> context;
        public MainWindow()
        {
            context = new List<ConfigModel>();
            
            context.Add(new ConfigModel("Unity", "/C \"bash.exe\" -c \"unity\""));
            context.Add(new ConfigModel("XFCE", "/C \"bash.exe\" -c \"xfce\""));
            context.Add(new ConfigModel("Cinnamon", "/C \"bash.exe\" -c \"cinnamon\""));
            context.Add(new ConfigModel("Windows Explorer", "/C \"explorer.exe\""));
            
            InitializeComponent();
            lstView.ItemsSource = context;
            foreach (var item in context)
            {
                item.readOrUpdateFromRegistry();
            }
        }

        private void Save_button_click(object sender, RoutedEventArgs e)
        {
            foreach (var item in context)
            {
                item.pushToRegistry();
            }
        }

        private void Reset_button_Click(object sender, RoutedEventArgs e)
        {
            String name = ((Button)sender).Tag.ToString();
            foreach (var item in context)
            {
                if (item.Name == name)
                {
                    item.Command = item.DefaultCommand;
                    
                }
            }
        }

        private void Disable_button_Click(object sender, RoutedEventArgs e)
        {
            foreach (var item in context)
            {
                item.delete();
            }
        }
    }
}
