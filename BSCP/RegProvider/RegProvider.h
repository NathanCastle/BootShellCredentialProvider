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

// This class is exported from the RegProvider.dll
class REGPROVIDER_API CRegProvider {
public:
	CRegProvider(void);
	~CRegProvider(void);
	LONG EnsureKeyPresent(WCHAR* key_name);
	LONG GetValueAt_sz(WCHAR* key_name, WCHAR* prop_name, WCHAR* result, DWORD* length);
	LONG GetSizeAt_sz(WCHAR* key_name, WCHAR* prop_name, DWORD* result);
	LONG EnsureKeyValueSet_sz(WCHAR* key_name, WCHAR* prop_name, WCHAR* value, DWORD* length);
};

extern REGPROVIDER_API int nRegProvider;

REGPROVIDER_API int fnRegProvider(void);
