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
        private String _console;
        private string _xmingCommand;
        private Boolean _usesXming;
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
        public String Console
        {
            get
            {
                return _console;
            }
            set
            {
                if (value != _console)
                {
                    _console = value;
                    OnPropertyChanged("Console");
                }
            }
        }
        public string XmingCommand
        {
            get => _xmingCommand;
            set
            {
                if (value != _xmingCommand)
                {
                    _xmingCommand = value;
                    OnPropertyChanged(nameof(XmingCommand));
                }
            }
        }
        public String DefaultCommand { get; set; }
        public String DefaultConsole { get; set; }

        public ConfigModel()
        {
        }

        public ConfigModel(String name, String defaultCommand, String defaultConsole, Boolean uses_xming = true, String defaultXmingString = "C:\\Program Files\\VcXsrv\\vcxsrv.exe\" :0 -clipboard -fullscreen -wgl")
        {
            this.Name = name;
            this.DefaultCommand = defaultCommand;
            this.DefaultConsole = defaultConsole;
            this._usesXming = uses_xming;
            this._xmingCommand = defaultXmingString;
        }

        /// <summary>
        /// Reads the value from the registry by name. If the command isn't there, populates it with default
        /// </summary>
        public void readOrUpdateFromRegistry()
        {
            var command_key = Registry.GetValue(get_full_name(), "command", null);
            var console_key = Registry.GetValue(get_full_name(), "console", null);
            var xming_key = Registry.GetValue(get_full_name(), "xming", null);
            var name_key = Registry.GetValue(get_full_name(), "name", null);
            var xming_command_key = Registry.GetValue(get_full_name(), "xming_command", null);

            if (xming_command_key == null)
            {
                Registry.SetValue(get_full_name(), "xming_command",  "C:\\Program Files\\VcXsrv\\vcxsrv.exe\" :0 -clipboard -fullscreen -wgl");
                xming_command_key = Registry.GetValue(app_key_base + "\\" + Name, "xming_command", null);
            }
            this.XmingCommand = xming_command_key.ToString();

            if (command_key == null)
            {
                //insert key & set value
                Registry.SetValue(get_full_name(), "command", this.DefaultCommand);
                command_key = Registry.GetValue(app_key_base + "\\" + Name, "command", null);
            } 

            this.Command = command_key.ToString();

            if (console_key == null)
            {
                Registry.SetValue(get_full_name(), "console", this.DefaultConsole);
                console_key = Registry.GetValue(app_key_base + "\\" + Name, "console", null);
            } 
            
            this.Console = console_key.ToString();

            if (xming_key == null)
            {
                Registry.SetValue(get_full_name(), "xming", this._usesXming.ToString());
            }

            if (name_key == null)
            {
                Registry.SetValue(get_full_name(), "name", this.Name);
            }
            
        }

        public void pushToRegistry()
        {
            Registry.SetValue(get_full_name(), "command", this.Command);
            Registry.SetValue(get_full_name(), "name", this.Name);
            Registry.SetValue(get_full_name(), "console", this.Console);
            Registry.SetValue(get_full_name(), "xming", this._usesXming.ToString());
            Registry.SetValue(get_full_name(), "xming_command", this._xmingCommand);
        }

        public void delete()
        {
            try
            {
                var hklm = Microsoft.Win32.Registry.LocalMachine;
                var subkey = hklm.OpenSubKey(app_key_base_light, true);
                subkey.DeleteSubKey(this.Name);
            } catch (ArgumentException)
            {
                return; //key not present
            }
            
        }

        private string get_full_name()
        {
            return app_key_base + "\\" + this.Name;
        }
    }
}
