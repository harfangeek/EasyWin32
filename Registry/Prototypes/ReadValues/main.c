/*
	Somme test about displaying values
*/

#include <windows.h>
#include <wchar.h>

HKEY GetOpenKey(HKEY hKey, wchar_t  * SubKey)
{
	//wchar_t * lpSubKey = SubKey; // Pas utile, on peut passer directement SubKey à RegOpenKeyExW
	HKEY phkResult;
	long lResult;

	wprintf(L"Ouverture de la cl\x82 : %ls\n\n", SubKey);

	lResult = RegOpenKeyExW(hKey, SubKey, 0, KEY_READ, &phkResult);
	if (lResult != ERROR_SUCCESS)
	{
		wprintf(L"Impossible d'ouvrir la cl\x82\n");
		return NULL; // La fonction doit retourner une valeur dans tous les cas
	}
	else
		return phkResult;
}

DWORD GetValueType(HKEY Key, wchar_t  * valueName) // DWORD à la place de int, histoire de garder les types Windows, renommé en GetValueType
{
	DWORD dwType;
	//DWORD dwSize; // Pas besoin de récupérer dwSize

	wprintf(L"Calcule du Type de la valeur : %ls \n\n", valueName);

	if (RegQueryValueExW(Key, valueName, NULL, &dwType, NULL,/*&dwSize*/NULL) == ERROR_SUCCESS)
	{
		wprintf(L"\t dwType : %ld \n\n", dwType);
		return dwType;
	}
	else
		return -1; // La fonction doit retourner une valeur dans tous les cas
}

DWORD GetValueSize(HKEY Key, wchar_t  * SubKey) // DWORD à la place de int, histoire de garder les types Windows, renommé en GetValueSize
{
	DWORD dwSize;
	// DWORD dwType; // Pas besoin de récupérer le type

	wprintf(L"Calcule de la taille de la valeur : %ls \n\n", SubKey);

	if (RegQueryValueExW(Key, SubKey, NULL,/*&dwType*/NULL, NULL, &dwSize) == ERROR_SUCCESS)
	{
		wprintf(L"\t dwSize : %ld \n\n", dwSize);
		return dwSize;
	}
	else
		return -1; // La fonction doit retourner une valeur dans tous les cas
}

BYTE * SetKeyDataSize(int dwSize)
{
	BYTE *lpData = NULL;

	wprintf(L"Allocation de la memoire pour la valeur :\n\n");
	lpData = (PBYTE)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, dwSize);
	wprintf(L"\t lpData en : %ld \n", sizeof(lpData));

	return lpData;
}

void GetDwordValue(HKEY Key, wchar_t * lpValueName, BYTE * lpData) // Renommé en GetDwordValue
{
	DWORD dwSize;
	DWORD dwType;

	long lResult = RegQueryValueExW(Key, lpValueName, NULL, &dwType, lpData, &dwSize);
	DWORD *pDwData = (DWORD*)lpData;
	DWORD dwData = *pDwData;
	wprintf(L"[?] Code Retour du Calcul de lpData: %ld \n\n", lResult);
	wprintf(L"\tValeur de la cl\x82 %s: %lu \n", lpValueName, dwData);
}

void GetSZValue(HKEY Key, wchar_t * lpValueName, byte * lpData) // Renommé en GetSZValue
{
	DWORD dwSize;
	DWORD dwType;
	long lResult = RegQueryValueExW(Key, lpValueName, NULL, &dwType, lpData, &dwSize);
	wchar_t *pSzData = (wchar_t*)lpData;

	wprintf(L"[?] Code Retour du Calcul de lpData: %ld \n\n", lResult);
	wprintf(L"\tValeur de la cl\x82 %s: %ls \n", lpValueName, pSzData);
}

int wmain(int argc, wchar_t** argv)
{
	HKEY hKey;
	DWORD valueType, valueSize;
	BYTE* pData;

	hKey = GetOpenKey(HKEY_CURRENT_USER, L"Test");

	valueType = GetValueType(hKey, L"value32");
	valueSize = GetValueSize(hKey, L"value32");
	pData = SetKeyDataSize(valueSize);
	GetDwordValue(hKey, L"value32", pData);
	HeapFree(GetProcessHeap(), 0, pData);

	valueType = GetValueType(hKey, L"str1");
	valueSize = GetValueSize(hKey, L"str1");
	pData = SetKeyDataSize(valueSize);
	GetSZValue(hKey, L"str1", pData);
	HeapFree(GetProcessHeap(), 0, pData);

	system("pause");
	return EXIT_SUCCESS;
}