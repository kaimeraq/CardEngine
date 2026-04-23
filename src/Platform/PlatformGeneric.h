#pragma once

// C++ 23 is required for this project
static_assert(__cplusplus >= 202302L);

typedef char        ANSICHAR;
typedef wchar_t	    WIDECHAR;
typedef WIDECHAR    GENCHAR;

struct GenericPlatform
{
public:
	static void LocalPrint(const GENCHAR* Str);
};