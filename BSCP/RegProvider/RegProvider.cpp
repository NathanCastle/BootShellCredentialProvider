// RegProvider.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "RegProvider.h"
#include "iostream"
#include <string>


// This is an example of an exported variable
REGPROVIDER_API int nRegProvider=0;

// This is an example of an exported function.
REGPROVIDER_API int fnRegProvider(void)
{
    return 42;
}

// This is the constructor of a class that has been exported.
// see RegProvider.h for the class definition
CRegProvider::CRegProvider()
{
    return;
}

CRegProvider::~CRegProvider(void)
{
}

LONG CRegProvider::EnsureKeyPresent(WCHAR* key_name)
{
	return ERROR_FILE_NOT_FOUND;
}

LONG CRegProvider::GetSizeAt_sz(WCHAR* key_name, WCHAR* prop_name, DWORD* result)
{
	HKEY root;
	REGSAM flag = KEY_QUERY_VALUE | KEY_ENUMERATE_SUB_KEYS | KEY_WOW64_64KEY;
	LONG query_result = RegOpenKeyEx(HKEY_LOCAL_MACHINE, NULL, NULL, flag, &root);
	query_result = RegGetValue(root, key_name, prop_name, RRF_RT_REG_SZ, NULL, NULL, result);
	if (query_result == ERROR_MORE_DATA) {

		return ERROR_SUCCESS;
	}
	else {
		return query_result;
	}
}

LONG CRegProvider::GetValueAt_sz(WCHAR* key_name, WCHAR* prop_name, WCHAR* result, DWORD* length)
{
	HKEY root;
	REGSAM flag = KEY_QUERY_VALUE | KEY_ENUMERATE_SUB_KEYS | KEY_WOW64_64KEY;
	RegOpenKeyEx(HKEY_LOCAL_MACHINE, NULL, NULL, flag, &root);
	LONG reg_res = RegGetValue(root, key_name, prop_name, RRF_RT_REG_SZ, NULL, result, length );
	return reg_res;
}

LONG CRegProvider::EnsureKeyValueSet_sz(WCHAR* key_name, WCHAR* prop_name, WCHAR* value, DWORD* length)
{
	LONG final_answer;
	WCHAR* val_exist = new WCHAR[*length];
	DWORD oldLength = *length; //save this because an existing value will overwrite it
	LONG first_check = GetValueAt_sz(key_name, prop_name, val_exist, length);
	if (first_check == ERROR_SUCCESS && !wcscmp(value, val_exist)) {
		final_answer = ERROR_SUCCESS; //key & value already set
	}
	else if (first_check == ERROR_SUCCESS) {
		//update value
		HKEY root;
		REGSAM flag = KEY_ALL_ACCESS | KEY_WOW64_64KEY;
		RegOpenKeyEx(HKEY_LOCAL_MACHINE, key_name, NULL, flag, &root);
		final_answer = RegSetKeyValue(root, NULL, prop_name, RRF_RT_REG_SZ, value, oldLength);
	}
	else {
		//create key and set value
		HKEY root;
		REGSAM flag = KEY_ALL_ACCESS | KEY_WOW64_64KEY;
		REGSAM flag_light = KEY_QUERY_VALUE | KEY_ENUMERATE_SUB_KEYS | KEY_WRITE | KEY_SET_VALUE | KEY_WOW64_64KEY;
		//final_answer = RegOpenKeyEx(HKEY_LOCAL_MACHINE, NULL, NULL, flag, &root);
		HKEY newkey;
		final_answer = RegCreateKeyEx(HKEY_LOCAL_MACHINE, key_name, NULL, NULL, REG_OPTION_NON_VOLATILE, flag, NULL, &newkey, NULL);
		if (final_answer == ERROR_SUCCESS) {
			final_answer = RegOpenKeyEx(HKEY_LOCAL_MACHINE, key_name, NULL, flag_light, &root);
			final_answer = RegSetKeyValue(root, NULL, prop_name, RRF_RT_REG_SZ, value, *length);
		}
		
	}

	delete val_exist;
	return final_answer;
}