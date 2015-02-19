/*
	List all subkeys of a given key
	ToDo : What is the key class? (empty by default, see user defined class)
*/

#include <windows.h>
#include <wchar.h>

#define KEY_NAME_LEN 255
#define KEY_CLASS_LEN 255

void listKeys(HKEY hKey);

int wmain(int argc, wchar_t **argv)
{
	HANDLE std = GetStdHandle(STD_OUTPUT_HANDLE);
	HKEY hKey;
	LSTATUS res;

	res = RegOpenKeyExW(HKEY_CURRENT_USER, L"Software", 0, KEY_EXECUTE, &hKey);
	if (res != ERROR_SUCCESS)
	{
		wprintf(L"Impossible d'ouvrir la cl\x82\n");
		system("pause");
		return EXIT_FAILURE;
	}

	listKeys(hKey);

	RegCloseKey(hKey); // Fermeture de la clé

	system("pause");

	return EXIT_SUCCESS;
}

void listKeys(HKEY hKey)
{
	DWORD i = 0;
	WCHAR keyName[KEY_NAME_LEN];
	DWORD keyNameLen = KEY_NAME_LEN;
	WCHAR keyClass[KEY_CLASS_LEN];
	DWORD keyClassLen = KEY_CLASS_LEN;
	LSTATUS res;

	while((res = RegEnumKeyExW(hKey, i, keyName, &keyNameLen, 0, keyClass, &keyClassLen, NULL)) == ERROR_SUCCESS)
	{
		wprintf(L"Name: %s\tClass: %s\n", keyName, keyClass);
		i++;
		keyNameLen = KEY_NAME_LEN;
		keyClassLen = KEY_CLASS_LEN;
	}
}
