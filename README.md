# BootShellCredentialProvider

BSCP lets you boot Windows directly into a Linux desktop experience, using Windows' native Logon UI and a combination of Xming & WSL upon login. 

This project consists of several components:

- Configurator: friendly desktop app for modifying the configuration
- RegProvider: helper library for interacting with the registry (nothing special here)
- ConfigurableShell: Replaces the Windows Explorer Shell at boot time. Checks the registry settings and loads the specified desktop environment (Windows Explorer, XFCE, or whatever else you can get to work)
- BootShellCredentialProvider: Plugin for WinLogon using the CredentialProvider v2 interface. This component shows you the available desktop environments and sets the selected one in the registry

Note: This project requires extensive modification to the registry to work and executes native code both before and after logging in. Use at own risk. 

Demo Pics:

[](../login.PNG)
[](../desktop.png)
