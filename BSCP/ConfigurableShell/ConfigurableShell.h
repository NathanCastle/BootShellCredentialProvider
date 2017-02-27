#pragma once

#include "resource.h"

static const PWSTR s_RegistryKey_Shells = L"SOFTWARE\\Castle\\BootShellCredentialProvider\\Shells";
static const PWSTR s_RegistryKey_Shell = L"SOFTWARE\\Castle\\BootShellCredentialProvider\\Shell";
static const PWSTR s_WinlogonKey = L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\WinLogon";
static const PWSTR s_WinLogonValue = L"Shell";
static const PWSTR s_WinLogonValueDefault = L"explorer.exe";
static const PWSTR s_WinLogonValueChanged = L"ConfigurableShell.exe";