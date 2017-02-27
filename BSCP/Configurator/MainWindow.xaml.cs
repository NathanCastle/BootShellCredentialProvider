using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
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
using Microsoft.Win32;

namespace Configurator
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        
        ObservableCollection<ConfigModel> context;
        static string credential_provider_guid = "ad471e7d-5bb2-4863-b317-faf3ad0f4d9d"; //identifies credential provider to system
        static string credential_key = "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Authentication\\Credential Providers\\";
        static string cp_name = "BootShellCredentialProvider";
        static string class_root_key = "HKEY_CLASSES_ROOT\\CLSID\\{" + credential_provider_guid + "}";


        public MainWindow()
        {
            context = new ObservableCollection<ConfigModel>();
            
            context.Add(new ConfigModel("Unity", "-c \"cd ~/ && ./unity.sh\"", "bash.exe"));
            context.Add(new ConfigModel("XFCE", "-c \"cd ~/ && ./xfce.sh\"", "bash.exe"));
            context.Add(new ConfigModel("Cinnamon", "-c \"cd ~/ && ./cinnamon.sh\"", "bash.exe"));
            context.Add(new ConfigModel("Windows Explorer", "/C \"explorer.exe\"", "cmd.exe", false));

            InitializeComponent();
            lstView.ItemsSource = context;
            foreach (var item in context)
            {
                item.readOrUpdateFromRegistry();
            }
        }

        private void Save_button_click(object sender, RoutedEventArgs e)
        {
            //set shells
            foreach (var item in context)
            {
                item.pushToRegistry();
            }
            //register credential provider
            Registry.SetValue(credential_key + "{" +credential_provider_guid + "}", "", cp_name);
            Registry.SetValue(class_root_key, "", cp_name);
            Registry.SetValue(class_root_key + "\\InprocServer32", "ThreadingModel", "Apartment");
            Registry.SetValue(class_root_key + "\\InprocServer32", "", cp_name + ".dll");
        }

        private void Reset_button_Click(object sender, RoutedEventArgs e)
        {
            String name = ((Button)sender).Tag.ToString();
            foreach (var item in context)
            {
                if (item.Name == name)
                {
                    item.Command = item.DefaultCommand;
                    item.Console = item.DefaultConsole;
                }
            }
        }
        private void Delete_button_Click(object sender, RoutedEventArgs e)
        {
            String name = ((Button)sender).Tag.ToString();
            ConfigModel itemToBeDeleted = null;
            foreach (var item in context)
            {
                if (item.Name == name)
                {
                    item.delete();
                    itemToBeDeleted = item;
                }
            }
            if (itemToBeDeleted != null)
            {
                context.Remove(itemToBeDeleted);
            }
            
        }

        private void Disable_button_Click(object sender, RoutedEventArgs e)
        {
            //delete shell keys
            foreach (var item in context)
            {
                item.delete();
            }
            //unregister credential provider
            var hklm = Microsoft.Win32.Registry.LocalMachine;
            try
            {
                var subkey = hklm.OpenSubKey("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Authentication\\Credential Providers", true);
                subkey.DeleteSubKey("{" + credential_provider_guid + "}");
            }
            catch (ArgumentException) { }
            var hkcl = Microsoft.Win32.Registry.ClassesRoot;
            try
            {
                var subkey = hkcl.OpenSubKey("CLSID\\{" + credential_provider_guid + "}", true);
                subkey.DeleteSubKey("InprocServer32");
                var parent_key = hkcl.OpenSubKey("CLSID", true);
                parent_key.DeleteSubKey("{" + credential_provider_guid + "}");
            } catch (ArgumentException) { }
        }

        private void New_Button_Click(object sender, RoutedEventArgs e)
        {
            context.Add(new ConfigModel("New", "-c \"\"", "bash.exe"));
            lstView.UpdateLayout();
        }
    }
}
