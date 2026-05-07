#pragma once

#include "Core/Logger.h"

#ifdef _MSC_VER
#define GENERATE_TRAP() __debugbreak()
#else
#define GENERATE_TRAP() __builtin_trap()
#endif

#if defined(__GNUC__) 
    #define likely(x) __builtin_expect(!!(x), 1) 
    #define unlikely(x) __builtin_expect(!!(x), 0) 
#else 
    #define likely(x) x 
    #define unlikely(x) x 
#endif

#define CRASH_FATAL(Cat,Fmt, ...)                                              \
    do {                                                                       \
        Logger::Get().log(Cat, Verbosity::Fatal, GENTEXT(Fmt), ##__VA_ARGS__); \
        GENERATE_TRAP();                                                       \
    } while(0)

#define ENSURE_INTERNAL(Con, Ver, Fmt, ...)                                        \
    do {                                                                           \
        if (unlikely(!(Con))) {                                                    \
            Logger::Get().log(Category::Assert, Ver, GENTEXT(Fmt), ##__VA_ARGS__); \
        }                                                                          \
    } while(0)

#define ENSURE(Con, Fmt, ...) \
    ENSURE_INTERNAL(Con, Verbosity::Error, Fmt, ##__VA_ARGS__)

#define ENSURE_WARN(Con, Fmt, ...) \
    ENSURE_INTERNAL(Con, Verbosity::Warning, Fmt, ##__VA_ARGS__)

#define ENSURE_FATAL(Con, Fmt, ...)                           \
    do {                                                      \
        if (unlikely(!(Con))) {                               \
            CRASH_FATAL(Category::Assert,Fmt, ##__VA_ARGS__); \
        }                                                     \
    } while(0) 