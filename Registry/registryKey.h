#ifndef REGISTRY_KEY_H
#define REGISTRY_KEY_H

	/**
	* This header provides functions for registry key exploring (open and close a key, explore subkeys, 
	* get information about a key)
	*/

	#include <Windows.h>
	#include <wchar.h>

	/**
	* Open the specified registry key
	* @param baseKey A handle to an open registry key
	* @param subkeyName The name of the registry subkey to be opened
	* @param rights A mask that specifies the desired access rights to the key to be opened
	* @param keyResult A pointer to an HKEY that receives a handle to the opened key.
	* @return ERROR_SUCCESS if the function succeeds, a nonzero error code defined in Winerror.h otherwise
	*/
	LSTATUS OpenKey(HKEY baseKey, LPCWSTR subkeyName, REGSAM rights, PHKEY keyResult);

	/**
	* Close the specified key
	* @param key Handle on the key to be closed
	* @return ERROR_SUCCESS if the function succeeds, a nonzero error code defined in Winerror.h otherwise
	*/
	LSTATUS CloseKey(HKEY key);

	/**
	* List all subkeys name of the specified key
	* @param key Handle on the key
	* @return a pointer to an array of null terminated WCHAR strings. The elements of this array and the array
			  itself have to be free by yourself using heapfree.
	*/
	LPWSTR* ListSubkeys(HKEY key);

	// TODO : Security descriptor, last modified timestamp, class

	/**
	* Get the key's last modified timestamp
	* @param key Handle on the key
	* @param time A pointer to a FILETIME structure that receives the last write time.
	*             The last write time change when the key or any of its value entries is modified.
	*
	* A voir : retourner directement une structure SYSTEMTIME (voir FileTimeToSystemTime)?
	*/
	void GetKeyLastModifiedDate(HKEY key, PFILETIME time);

	/**
	* Get the user-defined class of the key
	* @param key Handle on the key
	* @return a pointer to a null terminated WCHAR string. The array has to be free by yourself using heapfree.
	*
	* A voir : L'info est récupérable avec RegQueryInfoKey mais je ne sais pas ce que représente cette "user-defined class".
	*/
	LPWSTR GetKeyClass(HKEY key);

	/**
	* A voir : Récupérer le security descriptor de la clé.
	*/

#endif