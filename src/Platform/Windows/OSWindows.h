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

#include <windows.h>
#endif

class WindowsPlatform : GenericPlatform
{
public:
    static void LocalPrint(const GENCHAR* message)
    {
#ifdef PLATFORM_WINDOWS
        OutputDebugString(message);
#endif
    }
};

#ifdef PLATFORM_WINDOWS
typedef WindowsPlatform PlatformNotifier;
#endif