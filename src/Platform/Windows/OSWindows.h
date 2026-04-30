#pragma once

#include "Platform/PlatformGeneric.h"

#if defined(_WIN32) || defined(_WIN64)
    #ifndef PLATFORM_WINDOWS
        #define PLATFORM_WINDOWS
    #endif // !PLATFORM_WINDOWS
#endif

#ifdef PLATFORM_WINDOWS
    #ifndef NOMINMAX
        #define NOMINMAX
    #endif

    #ifndef WIN32_LEAN_AND_MEAN
        #define WIN32_LEAN_AND_MEAN
    #endif

    #if !defined(GENTEXT)
        #if defined(PLATFORM_GENCHAR_IS_GENCHAR16) && PLATFORM_GENCHAR_IS_GENCHAR16
            #define GENTEXT_REPLACE(x) u ## x
        #elif defined(UNICODE)
            #define GENTEXT_REPLACE(x) L ## x
        #else
            #define GENTEXT(x) x
        #endif

        #define GENTEXT(x) GENTEXT_REPLACE(x)
    #endif

    #include <fcntl.h>
    #include <io.h>
    #include <windows.h>
#endif

class WindowsPlatform : GenericPlatform
{
public:
    static void LocalPrint(GENCSTR message)
    {
#ifdef PLATFORM_WINDOWS
        OutputDebugString(message);
        wprintf(GENTEXT("%s"), message);
#endif
    }
};

#ifdef PLATFORM_WINDOWS
    typedef WindowsPlatform PlatformNotifier;
#endif