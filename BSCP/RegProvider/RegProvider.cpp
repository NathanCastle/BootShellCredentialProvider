// RegProvider.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "RegProvider.h"
#include "iostream"
#include <string>

// This is the constructor of a class that has been exported.
// see RegProvider.h for the class definition
CRegProvider::CRegProvider() : __alloced_strings()
{
    return;
}

CRegProvider::~CRegProvider(void) {
	for (std::list<WCHAR*>::iterator index = __alloced_strings.begin(); index != __alloced_strings.end(); index++) {
		WCHAR* str = *index;
		delete[] str;
	}
}

LONG CRegProvider::GetSizeAt_sz(__in WCHAR* key_name, __in WCHAR* prop_name, __out DWORD* result)
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

LONG CRegProvider::GetValueAt_sz(__in WCHAR* key_name, __in WCHAR* prop_name, __out WCHAR* result, __inout DWORD* length)
{
	HKEY root;
	REGSAM flag = KEY_QUERY_VALUE | KEY_ENUMERATE_SUB_KEYS | KEY_WOW64_64KEY;
	RegOpenKeyEx(HKEY_LOCAL_MACHINE, NULL, NULL, flag, &root);
	LONG reg_res = RegGetValue(root, key_name, prop_name, RRF_RT_REG_SZ, NULL, result, length );
	return reg_res;
}

LONG CRegProvider::EnsureKeyValueSet_sz(__in WCHAR* key_name, __in WCHAR* prop_name, __in WCHAR* value, __in DWORD* cblength)
{
	LONG final_answer;
	WCHAR* val_exist = new WCHAR[*cblength / 2 + 1];
	DWORD cclength = *cblength / 2 + 1;
	DWORD oldLength = *cblength; //save this because an existing value will overwrite it
	LONG first_check = GetValueAt_sz(key_name, prop_name, val_exist, &cclength);
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
			final_answer = RegSetKeyValue(root, NULL, prop_name, RRF_RT_REG_SZ, value, oldLength);
		}
		
	}

	delete val_exist;
	return final_answer;
}

LONG CRegProvider::CountSubkeys(WCHAR* key_name, DWORD* count, DWORD* max_length) {
	HKEY root;
	REGSAM flag = KEY_QUERY_VALUE | KEY_ENUMERATE_SUB_KEYS | KEY_WOW64_64KEY;
	RegOpenKeyEx(HKEY_LOCAL_MACHINE, key_name, NULL, flag, &root);
	return RegQueryInfoKey(root, NULL, NULL, NULL, count, max_length, NULL, NULL, NULL, NULL, NULL, NULL);
}

LONG CRegProvider::GetSubKey(__in WCHAR* key_name, __in DWORD index, __out WCHAR* result, __inout DWORD* length) {
	HKEY root;
	REGSAM flag = KEY_QUERY_VALUE | KEY_ENUMERATE_SUB_KEYS | KEY_WOW64_64KEY;
	LONG res = RegOpenKeyEx(HKEY_LOCAL_MACHINE, key_name, NULL, flag, &root);
	return RegEnumKeyEx(root, index, result, length, NULL, NULL, NULL, NULL);
}

WCHAR* CRegProvider::pwszGetSubKey(__in WCHAR* key_name, __in DWORD index, __inout_opt DWORD* cblength, __out DWORD* cclength) {
	//get # of subkeys & size of largest subkey (in chars, excluding null terminator)
	DWORD count_subkeys;
	HKEY root;
	REGSAM flag = KEY_QUERY_VALUE | KEY_ENUMERATE_SUB_KEYS | KEY_WOW64_64KEY;
	RegOpenKeyEx(HKEY_LOCAL_MACHINE, key_name, NULL, flag, &root);
	RegQueryInfoKey(root, NULL, NULL, NULL, &count_subkeys, cclength, NULL, NULL, NULL, NULL, NULL, NULL);
	//check for invalid index
	if (index >= count_subkeys) {
		return NULL;
	}
	*cclength += 1;
	RegEnumKeyEx(root, index, NULL, cclength, NULL, NULL, NULL, NULL);
	WCHAR* result = new WCHAR[*cclength]; 
	__alloced_strings.push_back(result); //record so we can delete later
	*cclength += 1;
	RegEnumKeyEx(root, index, result, cclength, NULL, NULL, NULL, NULL);
	
	if (cblength != NULL) {
		*cblength = *cclength * 2 + 2; //wchar to bytes
	}
	return result;
}

WCHAR* CRegProvider::pwszGetValueAt_sz(__in WCHAR* key_name, __in WCHAR* value_name, __inout DWORD* cblength, __out DWORD* cclength) {
	//need cblength internally because some win32 APIs count in bytes
	HKEY root;
	REGSAM flag = KEY_QUERY_VALUE | KEY_ENUMERATE_SUB_KEYS | KEY_WOW64_64KEY;
	RegOpenKeyEx(HKEY_LOCAL_MACHINE, key_name, NULL, flag, &root);
	RegQueryInfoKey(root, NULL, NULL, NULL, NULL, NULL, NULL, NULL, cclength, NULL, NULL, NULL); //get biggest length for value (chars)
	//get size for specific value in bytes
	*cblength = *cclength * 2 + 2; //longest length in bytes
	RegGetValue(root, NULL, value_name, RRF_RT_REG_SZ, NULL, NULL, cblength);
	//get and return value
	*cblength += 1;
	*cclength = *cblength / 2;
	WCHAR* result = new WCHAR[*cclength];
	__alloced_strings.push_back(result); //record so we can delete la
	RegGetValue(root, NULL, value_name, RRF_RT_REG_SZ, NULL, result, cblength);
	return result;
}