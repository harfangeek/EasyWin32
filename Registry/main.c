#include <windows.h>
#include <wchar.h>

/*
Registry Element	Size Limit
Key name			255 characters. The key name includes the absolute path of the key in the registry, always starting at a base key, for example, HKEY_LOCAL_MACHINE.
Value name			16,383 characters
					Windows 2000:  260 ANSI characters or 16,383 Unicode characters.
Value				Available memory (latest format)
					1 MB (standard format)
Tree				A registry tree can be 512 levels deep. You can create up to 32 levels at a time through a single registry API call.
*/

int wmain(int argc, wchar_t** argv)
{

	return EXIT_SUCCESS;
}