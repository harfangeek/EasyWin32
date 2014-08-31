#ifndef REGISTRY_VALUE_H
#define REGISTRY_VALUE_H

	/**
	* This header provides functions for registry key values management
	*/

	#include <Windows.h>
	#include <wchar.h>

	/**
	* List all values names of the specified key
	* @param key Handle on the key
	* @return a pointer to an array of null terminated WCHAR strings. The elements of this array and the array 
	*		  itself have to be free by yourself using heapfree.
	*/
	LPWSTR* ListValues(HKEY key);

	/**
	* Get the type of the given value, of the given key
	* @param key Handle on the key
	* @param valueName Name of the wanted value. If valueName is NULL or an empty string, "", the function 
	*				   retrieves the type for the key's unnamed or default value, if any. 
	* @return the type of the given value of the given key in byte, or -1 if the value doesn't exist
	*/
	DWORD GetValueType(HKEY key, LPCWSTR valueName);
	
	/**
	* Get the size of the given value, of the given key, in byte
	* @param key Handle on the key
	* @param valueName Name of the wanted value. If valueName is NULL or an empty string, "", the function 
	*				   retrieves the size for the key's unnamed or default value, if any. 
	* @return the size of the given value of the given key in byte, or -1 if the value doesn't exist
	*/
	size_t GetValueSize(HKEY key, LPCWSTR valueName);

	/**
	* Get the data of the given value, of the given key
	* @param key Handle on the key
	* @param valueName Name of the wanted value. If valueName is NULL or an empty string, "", the function 
	*				   retrieves the type for the key's unnamed or default value, if any. 
	* @param valueSize Optionnal. A pointer to a size_t, who will contain the size of the returned array. 
					   It can also be retrieved using GetValueSize.
	* @return a pointer to a BYTE array representing the data of the given value of the given key, or NULL if 
	*		  the value doesn't exist. The array has to be free by yourself using heapfree.
	*/
	BYTE* GetValueData(HKEY key, LPCWSTR valueName, size_t* valueSize);

#endif