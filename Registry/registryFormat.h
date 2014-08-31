#ifndef REGISTRY_FORMAT_H
#define REGISTRY_FORMAT_H

	/**
	* This header provides functions for data formatting
	*/

	#include <Windows.h>
	#include <wchar.h>

	/**
	* byte array little endian to dword
	*/
	DWORD32 byteArrayToDword(BYTE* rawData, Endianness

	/**
	* byte array big endian to dword
	*/

	/**
	* byte array little endian to qword
	*/

	/**
	* byte array big endian to qword
	*/

	/**
	* byte array to string
	*/

	/**
	* byte array to array of strings
	*/

#endif