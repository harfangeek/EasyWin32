#ifndef REGISTRY_FORMAT_H
#define REGISTRY_FORMAT_H

	/**
	* This header provides functions for data formatting
	*/

	#include <Windows.h>
	#include <wchar.h>
	#include <stdint.h>

	/**
	* Convert a value represented by a BYTE array into a DWORD according to the origin (determined by the value's type), 
	* and to the system endianness. System endianness is automatically determined.
	* @param data An array of BYTE representing the data to convert
	* @param dataLen Size of the data array
	* @param valueType The type of the value to convert. This, will determine the origina endianness?
	* 	 valueType can be REG_DWORD or REG_DWORD_LITTLE_ENDIAN for little endian origin, REG_DWORD_BIG_ENDIAN
	* 	 for big endian origin. If an other type is given, little endian origin will be chosen by default
	* @return the converted DWORD value
	*/
	DWORD byteArrayToDword(BYTE* data, size_t dataLen, DWORD valueType);

	/**
	* Convert a value represented by a BYTE array into a QWORD according to the system endianness. Origin endianness
	* is forced to little_endian because there is no such things as REG_QWORD_BIG_ENDIAN defined by win32
	* System endianness is automatically determined.
	* @param data An array of BYTE representing the data to convert
	* @param dataLen Size of the data array
	* @return the converted DWORD value
	* 
	* @todo Voir si on peut tout de même être confronté à une valeur QWORD en big endian.
	*/
	QWORD byteArrayToDword(BYTE* data, size_t dataLen);

	/**
	* Convert a BYTE array into a null terminated WCHAR string
	* @param data An array of BYTE representing the data to convert
	* @param dataLen Size of the data array
	* @return a pointer to a null terminated WCHAR string. This string has to be free by yourself usin heapfree.
	* 
	* @todo différence entre des chaines ascii et unicode à prendre en compte?
	*/
	LPWSTR byteArrayToString(BYTE* data, size_t dataLen);

	/**
	* Convert a BYTE array into an array of null terminated WCHAR strings
	* @param data An array of BYTE representing the data to convert
	* @param dataLen Size of the data array
	* @return a pointer to an array of null terminated WCHAR string. 
	* 	  This array and each string of the array has to be free by yourself usin heapfree.
	* 
	* @todo différence entre des chaines ascii et unicode à prendre en compte?
	*/
	LPWSTR byteArrayToStringArray(BYTE* data, size_t dataLen, int nbStrings);

#endif
