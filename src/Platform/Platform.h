#pragma once

#if defined(_WIN32) || defined(_WIN64)
    #ifndef PLATFORM_WINDOWS
        #define PLATFORM_WINDOWS
    #endif
#endif

#ifdef PLATFORM_WINDOWS
    #include "Platform/Windows/OSWindows.h"
#endif

struct MessageNotify 
{
public:
    static void SendString(GENCSTR message) 
    {
        PlatformNotifier::LocalPrint(message);
    }
};