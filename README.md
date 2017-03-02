# BootShellCredentialProvider - Bringing Linux DEs to Windows

BSCP lets you boot Windows directly into a Linux desktop experience, using Windows' native Logon UI and a combination of Xming & WSL upon login. 

![](/login.PNG)
![](/xfce.gif)
![](/mate.gif)
![](/kde.gif)

## Getting Started

Prerequisites:

- VcXsrv must be installed. This is a free Xming alternative that happens to be more stable and featured. It is available on chocolatey, otherwise: https://sourceforge.net/projects/vcxsrv/ 
- Windows Subsystem for Linux, including the bash environment, is installed and working
- You have some sense of which Linux DEs you'd like to explore and have installed them through WSL. See [here](https://github.com/NathanCastle/BootShellCredentialProvider/blob/master/BSCP/Configurator/wsl_setup.sh) for inspiration/a runnable script to do it for you. Note: doing everything in that file *should* work, but will take a long time regardless.

Installing & Configuring:

- Download and run the installer from [here](https://github.com/NathanCastle/BootShellCredentialProvider/releases). Do not change any of the defaults; the defaults work. 
- Run BSCP Configurator (a shortcut in your Start Menu)
- Configure the settings as desired. Note that the defaults should work with the environment created by the setup scritpt mentioned above. 
- In the unlikely event that BSCP Configurator crashes upon attempting to save, you have a permissions issue. Try running again as an administrator. If that doesn't work, you probably need to give yourself Full Control permissions on `HKLM\SOFTWARE\Microsoft\Windows NT\CurrentVersion\WinLogon`.
- Sign out and behold!

Usage Notes:

- Ctrl+Alt+Del still works while in the Linux DEs. This is how you can sign out, start the Task Manager, etc.
- Win+R does not work while Explorer is not running as the system Shell. Use Task Manager (through Ctrl+Alt+Del) to start Windows programs
- There's a chance Windows Explorer (as file explorer, not shell) will run in the foreground when the DE starts. You can safely ignore or close it. 
- The uninstaller isn't particularly smart. You'll want to use the Configurator to disable the feature first, then run the uninstaller.
- Once you've installed this, you'll want to use it as your primary way of logging in; It has no way of updating the shell settings if you log in through another Credential Provider (e.g. Pin logon or Windows Hello). 

## About the Project
This project consists of several components:

- Configurator: friendly desktop app for modifying the configuration
- RegProvider: helper library for interacting with the registry (nothing special here)
- ConfigurableShell: Replaces the Windows Explorer Shell at boot time. Checks the registry settings and loads the specified desktop environment (Windows Explorer, XFCE, or whatever else you can get to work)
- BootShellCredentialProvider: Plugin for WinLogon using the CredentialProvider v2 interface. This component shows you the available desktop environments and sets the selected one in the registry

## Risks, Security & Full Disclosure

You probably shouldn't do this on anything resembling a production/mission-critical system, for several reasons:

- You're running my unmanaged c++ code inside WinLogon. If my code crashes, WinLogon crashes; you will not be able to use your PC if this happens. 
- My unmanaged code is handling your Windows password. This is borrowed from Microsoft's sample/template. Skepticism is encouraged.
- Components of this system rely on weakening the security of various system registry keys. These are critical to Windows' ability to present a coherent desktop experience.
- This is my second serious C++ project ever, and first with the Win32 API. Good luck.

## Contribution & Feedback

I'd appreciate any and all (constructive) feedback on this project, and will of course accept PRs. Feel free to file issues on this project if you have anything to share. 

## Licensing

Most of this project is released under the MIT License. The Credential Provider component is released under the MS-LPL license because it is derived from the SampleV2CredentialProvider project. 
