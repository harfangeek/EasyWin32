/*
	List all values from a given key (name, size and type)
	ToDo: Display values
*/

#include <windows.h>
#include <wchar.h>

#define VALUE_NAME_LEN 512
#define VALUE_TYPE_LEN 32

void listKeyValues(HKEY Key);
void getValueTypeStr(DWORD valueType, LPWSTR valueTypeStr);

int wmain(int argc, wchar_t **argv)
{
	PDWORD cChars = NULL;
	HANDLE std = GetStdHandle(STD_OUTPUT_HANDLE);
	HKEY hKey;
	LSTATUS res;

	WCHAR keyClass[1024];
	DWORD keyClassLen = 1024;
	DWORD lst;

	// Ouverture de la clé
	res = RegOpenKeyExW(HKEY_CURRENT_USER, L"Test", 0, KEY_EXECUTE, &hKey);
	if (res != ERROR_SUCCESS)
	{
		wprintf(L"Impossible d'ouvrir la cl\x82\n");
		system("pause");
		return EXIT_FAILURE;
	}

	listKeyValues(hKey);
	/*lst = RegQueryInfoKeyW(hKey, keyClass, &keyClassLen, 0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
	wprintf(L"%s", keyClass);

	RegQueryInfoKeyW(hKey, NULL, NULL, 0, NULL, NULL, NULL, NULL, NULL, NULL, &lst, NULL);*/

	RegCloseKey(hKey); // Fermeture de la clé

	system("pause");

	return EXIT_SUCCESS;
}

void listKeyValues(HKEY hKey)
{
	LONG res;
	DWORD i = 0;
	WCHAR valueName[VALUE_NAME_LEN];
	DWORD valueNameLen;
	DWORD valueType;
	WCHAR valueTypeStr[VALUE_TYPE_LEN];

	do
	{
		valueNameLen = VALUE_NAME_LEN; // Besoin de remettre la longueur du nom car elle est changé par RegEnumValue
		res = RegEnumValueW(hKey, i++, valueName, &valueNameLen, 0, &valueType, NULL, NULL); // On pourrait récupéré la donnée en même temps via les deux derniers paramètres
		if (res == ERROR_SUCCESS)
		{
			valueName[valueNameLen] = '\0'; // Au cas où, la présence du null byte n'est pas certifié
			getValueTypeStr(valueType, valueTypeStr); // On récupère le type de la valeur sous forme d'une string
			wprintf(L"Name: %s\tSize: %d\tType: %s\n", valueNameLen > 0 ? valueName : L"(default)", valueNameLen, valueTypeStr);
		}
	} while (res == ERROR_SUCCESS);

	if (res == ERROR_NO_MORE_ITEMS)
		wprintf(L"\n#END#\n");
	else
		wprintf(L"\n#ERROR#\n");
}

// Renvoie le type de valeur correspondant à valueType sous la forme d'une string
void getValueTypeStr(DWORD valueType, LPWSTR valueTypeStr)
{
	switch (valueType)
	{
	case REG_BINARY:
		lstrcpyW(valueTypeStr, L"REG_BINARY");
		break;
	case REG_DWORD:
		lstrcpyW(valueTypeStr, L"REG_DWORD");
		break;
	case REG_DWORD_BIG_ENDIAN:
		lstrcpyW(valueTypeStr, L"REG_DWORD_BIG_ENDIAN");
		break;
	case REG_EXPAND_SZ:
		lstrcpyW(valueTypeStr, L"REG_EXPAND_SZ");
		break;
	case REG_LINK:
		lstrcpyW(valueTypeStr, L"REG_LINK");
		break;
	case REG_MULTI_SZ:
		lstrcpyW(valueTypeStr, L"REG_MULTI_SZ");
		break;
	case REG_NONE:
		lstrcpyW(valueTypeStr, L"REG_NONE");
		break;
	case REG_QWORD:
		lstrcpyW(valueTypeStr, L"REG_QWORD");
		break;
	case REG_SZ:
		lstrcpyW(valueTypeStr, L"REG_SZ");
		break;
	default:
		lstrcpyW(valueTypeStr, L"OTHER");
	}
}