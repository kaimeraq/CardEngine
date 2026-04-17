#pragma once

typedef char        ANSICHAR;
typedef wchar_t	    WIDECHAR;
typedef WIDECHAR    GENCHAR;

struct GenericPlatform
{
public:
	static void LocalPrint(const GENCHAR* Str);
};