#pragma once

#include "Platform/PlatformGeneric.h"

#ifdef PLATFORM_WINDOWS
    #if !defined(GENTEXT)
        #if defined(UNICODE)
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