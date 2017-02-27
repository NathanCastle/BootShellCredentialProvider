// BSCP.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "Strsafe.h"
#include "Shellapi.h"
#include "../../BSCP/RegProvider/RegProvider.h"


int main()
{
	/*
	CONSOLE_READCONSOLE_CONTROL tControl;
	tControl.nInitialChars = 0;
	tControl.dwCtrlWakeupMask = L'\n';
	WCHAR* first_message = TEXT("Enter reg key to open \r\n");
	WCHAR* second_message = TEXT("Enter value to open \r\n");
	HANDLE hwnd_console_out = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hwnd_console_in = GetStdHandle(STD_INPUT_HANDLE);
	WCHAR key_name[100]; //reg key in HKLM to read
	WCHAR prop_name[100]; //reg key property to read
	DWORD len_key = 100;
	DWORD len_prop = 100;
	DWORD len_output = 0;
	//WCHAR* output;
	*/
	CRegProvider prov = CRegProvider();
	int index = 0;
	while (true) {
		//get values
		/*WriteConsole(hwnd_console_out, first_message, _tcslen(first_message), NULL, NULL);
		ReadConsole(hwnd_console_in, &key_name, len_key, &len_key, &tControl);
		WCHAR* key_rightsized = new WCHAR[len_key + 1];
		StringCchCopy(key_rightsized, len_key -1, key_name);

		WriteConsole(hwnd_console_out, second_message, _tcslen(second_message), NULL, NULL);
		ReadConsole(hwnd_console_in, &prop_name, len_key, &len_prop, &tControl);
		WCHAR* prop_rightsized = new WCHAR[len_prop - 1];
		StringCchCopy(prop_rightsized, len_prop - 1, prop_name);

		//print entered values
		WriteConsole(hwnd_console_out, key_name, len_key, NULL, NULL);
		WriteConsole(hwnd_console_out, prop_name, len_prop, NULL, NULL);

		prov.GetSizeAt_sz(key_rightsized, prop_rightsized, &len_output);
		output = new WCHAR[len_output/2];
		prov.GetValueAt_sz(key_rightsized, prop_rightsized, output, &len_output);
		*/
		/*
		CRegProvider prov = CRegProvider();
		WCHAR* prop_value = TEXT("Windows Explorer");
		WCHAR* prop_value_2 = TEXT("/C explorer.exe");
		WCHAR* prop_name_1 = TEXT("command");
		WCHAR* key_name = TEXT("SOFTWARE\\Castle\\BootShellCredentialProvider\\Shells\\Default");
		DWORD prop_val_length = (_tcslen(prop_value) + 1) *2; //extra bytes for terminating char
		DWORD prop_val_length_2 = (_tcslen(prop_value) + 1) * 2;
		//LONG res = prov.EnsureKeyValueSet_sz(key_name, TEXT("name"), prop_value, &prop_val_length);
		LONG res2 = prov.EnsureKeyValueSet_sz(key_name, TEXT("command"), prop_value_2, &prop_val_length_2);
		DWORD length = 0;
		prov.GetSizeAt_sz(key_name, prop_name_1, &length);
		WCHAR* output = new WCHAR[length / 2];
		prov.GetValueAt_sz(key_name, prop_name_1, output, &length);
		WriteConsole(hwnd_console_out, output, length/2, NULL, NULL);
		ShellExecute(NULL, TEXT("Open"), TEXT("cmd.exe"), output, NULL, SW_HIDE);
		system("pause");
		delete output;
		//delete prop_rightsized;
		//delete key_rightsized;
		*/
		/*WCHAR* key_name = TEXT("SOFTWARE\\Castle\\BootShellCredentialProvider\\Shells");
		DWORD count_subkeys = 0;
		DWORD max_length = 0;
		prov.CountSubkeys(key_name, &count_subkeys, &max_length);
		
		int index = 0;
		while (index < count_subkeys) {
			WCHAR* subkey_name = new WCHAR[max_length];
			DWORD length_subkey = max_length * 2; //need bytes
			LONG r_result = prov.GetSubKey(key_name, index, subkey_name, &length_subkey);
			WCHAR* final_answer = new WCHAR[length_subkey + 1];
			StringCchCopy(final_answer, length_subkey + 1, subkey_name);
			WriteConsole(hwnd_console_out, final_answer, length_subkey + 1, NULL, NULL);
			index++;
		}*/
		/*DWORD dwSelectedItem = 0;
		HRESULT hr;
		//load up correct subkey
		DWORD max_length = 150;
		WCHAR* subkey_name = new WCHAR[max_length];
		DWORD length_subkey = max_length; //need bytes
		LONG r_result = prov.GetSubKey(TEXT("SOFTWARE\\Castle\\BootShellCredentialProvider\\Shells"), dwSelectedItem, subkey_name, &length_subkey);
		//get command for selected option
		WCHAR* command_base = TEXT("SOFTWARE\\Castle\\BootShellCredentialProvider\\Shells\\");
		DWORD command_length = _tcslen(command_base) + length_subkey + 2;
		WCHAR* command_key = new WCHAR[command_length];
		StringCchCopy(command_key, _tcslen(command_base) + 2, command_base);
		WCHAR* command_pre = new WCHAR[600];
		StringCchCat(command_key, command_length, subkey_name);
		LONG res = prov.GetValueAt_sz(command_key, TEXT("command"), command_pre, &command_length); //get length

		WCHAR* control_key_name = TEXT("SOFTWARE\\Castle\\BootShellCredentialProvider\\Shell");
		res = prov.EnsureKeyValueSet_sz(control_key_name, TEXT("name"), subkey_name, &length_subkey);
		res += prov.EnsureKeyValueSet_sz(control_key_name, TEXT("command"), command_pre, &command_length);

		delete subkey_name;
		delete command_pre;
		delete command_key;*/
		PWSTR s_RegistryKey_Shells = L"SOFTWARE\\Castle\\BootShellCredentialProvider\\Shells";
		PWSTR s_RegistryKey_Shells_s = L"SOFTWARE\\Castle\\BootShellCredentialProvider\\Shells\\";
		PWSTR s_RegistryKey_Shell = L"SOFTWARE\\Castle\\BootShellCredentialProvider\\Shell";
		DWORD _dwComboIndex = index;
		//get subkey for selected option
		DWORD ccSubkeyLength = 0;
		DWORD cbSubkeyLength = 0;
		WCHAR* subkey_name = prov.pwszGetSubKey(s_RegistryKey_Shells, _dwComboIndex, &cbSubkeyLength, &ccSubkeyLength);
		//get command subkey for selected option
		DWORD command_length = wcslen(s_RegistryKey_Shells) + ccSubkeyLength + 2;
		WCHAR* command_key = new WCHAR[command_length];
		StringCchCopy(command_key, wcslen(s_RegistryKey_Shells_s) + 2, s_RegistryKey_Shells_s);
		StringCchCat(command_key, command_length, subkey_name);
		//get command for selected option
		DWORD ccCommLength = 0;
		DWORD cbCommLength = 0;
		WCHAR* command_pre = prov.pwszGetValueAt_sz(command_key, TEXT("command"), &cbCommLength, &ccCommLength);
		//get console for selected option
		DWORD ccConsoleLength = 0;
		DWORD cbConsoleLength = 0;
		WCHAR* console_name = prov.pwszGetValueAt_sz(command_key, TEXT("console"), &cbConsoleLength, &ccConsoleLength);
		//get xming for selected option
		DWORD ccXmingLength = 0;
		DWORD cbXmingLength = 0;
		WCHAR* xming_value = prov.pwszGetValueAt_sz(command_key, TEXT("xming"), &cbXmingLength, &ccXmingLength);
		//set values
		prov.EnsureKeyValueSet_sz(s_RegistryKey_Shell, TEXT("name"), subkey_name, &cbSubkeyLength);
		prov.EnsureKeyValueSet_sz(s_RegistryKey_Shell, TEXT("command"), command_pre, &cbCommLength);
		prov.EnsureKeyValueSet_sz(s_RegistryKey_Shell, TEXT("console"), console_name, &cbConsoleLength);
		prov.EnsureKeyValueSet_sz(s_RegistryKey_Shell, TEXT("xming"), xming_value, &cbXmingLength);
		//ShellExecute(NULL, TEXT("Open"), TEXT("bash.exe"), TEXT("/K \"bash.exe\" "), NULL, SW_SHOW);
		//system("pause");
		index += 1;
	}
    return 0;
}

