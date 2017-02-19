using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Win32;
using System.ComponentModel;

namespace Configurator
{
    public class ConfigModel : INotifyPropertyChanged
    {
        public static string app_key_base = "HKEY_LOCAL_MACHINE\\SOFTWARE\\Castle\\BootShellCredentialProvider\\Shells";
        public static string app_key_base_light = "SOFTWARE\\Castle\\BootShellCredentialProvider\\Shells";

        public event PropertyChangedEventHandler PropertyChanged;
        protected void OnPropertyChanged(string name)
        {
            PropertyChangedEventHandler handler = PropertyChanged;
            if (handler != null) handler(this, new PropertyChangedEventArgs(name));
        }

        private String _name;
        private String _command;
        private Boolean _isEnabled;
        public String Name
        {
            get
            {
                return _name;
            }
            set
            {
                if (value != _name)
                {
                    _name = value;
                    OnPropertyChanged("Name");
                }
            }
        }
        public String Command
        {
            get
            {
                return _command;
            }
            set
            {
                if (value != _command)
                {
                    _command = value;
                    OnPropertyChanged("Command");
                }
            }
        }
        public String DefaultCommand { get; set; }
        public Boolean IsEnabled
        {
            get
            {
                return _isEnabled;
            }
            set
            {
                if (value != _isEnabled)
                {
                    _isEnabled = value;
                    OnPropertyChanged("IsEnabled");
                }
            }
        }

        public ConfigModel()
        {
            this.IsEnabled = true;
        }

        public ConfigModel(String name, String defaultCommand)
        {
            this.Name = name;
            this.DefaultCommand = defaultCommand;
        }

        /// <summary>
        /// Reads the value from the registry by name. If the command isn't there, populates it with default
        /// </summary>
        public void readOrUpdateFromRegistry()
        {
            var key = Registry.GetValue(app_key_base + "\\" + Name, "command", null);
            if (key == null)
            {
                //insert key & set value
                Registry.SetValue(get_full_name(), "command", this.DefaultCommand);

            } else
            {
                this.Command = key.ToString();
            }
        }

        public void pushToRegistry()
        {
            Registry.SetValue(get_full_name(), "command", this.Command);
            Registry.SetValue(get_full_name(), "name", this.Name);
        }

        public void delete()
        {
            var hklm = Microsoft.Win32.Registry.LocalMachine;
            var subkey = hklm.OpenSubKey(app_key_base_light, true);
            subkey.DeleteSubKey(this.Name);
        }

        private string get_full_name()
        {
            return app_key_base + "\\" + this.Name;
        }
    }
}
