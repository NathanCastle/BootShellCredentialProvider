// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the REGPROVIDER_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// REGPROVIDER_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef REGPROVIDER_EXPORTS
#define REGPROVIDER_API __declspec(dllexport)
#else
#define REGPROVIDER_API __declspec(dllimport)
#endif

#include <list>

// This class is exported from the RegProvider.dll
class REGPROVIDER_API CRegProvider {
public:
	CRegProvider(void);
	~CRegProvider(void);
	LONG GetValueAt_sz(__in WCHAR* key_name, __in WCHAR* prop_name, __out WCHAR* result, __out DWORD* length);
	LONG GetSizeAt_sz(__in WCHAR* key_name, __in WCHAR* prop_name, __out DWORD* result);
	LONG EnsureKeyValueSet_sz(__in WCHAR* key_name, __in WCHAR* prop_name, __in WCHAR* value, __in DWORD* cblength);
	LONG CountSubkeys(__in WCHAR* key_name, __out DWORD* count, __out DWORD* max_length);
	LONG GetSubKey(__in WCHAR* key_name, __in DWORD index, __out WCHAR* result, __out DWORD* length);
	WCHAR* pwszGetSubKey(__in WCHAR* key_name, __in DWORD index, __out DWORD* cblength, __out DWORD* cclength);
	WCHAR* pwszGetValueAt_sz(__in WCHAR* key_name, __in WCHAR* value_name, __out DWORD* cblength, __out DWORD* cclength);
private:
#pragma warning (disable: 4251)
	std::list<WCHAR*> __alloced_strings; //allocated strings (for results), to facilitate deletion
};

extern REGPROVIDER_API int nRegProvider;

REGPROVIDER_API int fnRegProvider(void);
