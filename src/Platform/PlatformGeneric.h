#pragma once

#include <string>
#include <format>

// C++ 23 is required for this project
static_assert(__cplusplus >= 202302L);

typedef char				ANSICHAR;
typedef unsigned char		UANSICHAR;
typedef wchar_t				GENCHAR;

typedef ANSICHAR*			ANSICSTRMUT;
typedef const ANSICHAR*		ANSICSTR;
typedef const UANSICHAR*	UANSICSTR;
typedef const GENCHAR*		GENCSTR;

typedef std::string			STDSTRING;
typedef std::wstring		GENSTRING;

template<typename... Args>
using GENSTRINGFMT = std::basic_format_string<GENCHAR, std::type_identity_t<Args>...>;

struct GenericPlatform
{
public:
	static void LocalPrint(GENCSTR Str);
};