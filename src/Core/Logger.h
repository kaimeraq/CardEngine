#pragma once
#include "Core/Engine.h"
#include "Platform/Platform.h"
#include <format>
#include <array>
#include <cstdarg>
#include <mutex>

#ifndef LOGGING
    #define LOGGING 2
#endif

enum class Category : uint8_t
{
    Application,
    Core,
    Gameplay,
    Renderer,
};

enum class Verbosity : uint8_t
{
    Fatal,
    Error,
    Warning,
    Log,
    Verbose
};

class Logger {
    Logger() {}
    std::mutex logMutex_;

public:
    bool bVTSupported = false;

    static Logger& Get() {
        static Logger instance;
        return instance;
    }

    template<typename... Args>
    void log(Category category, Verbosity verbosity, GENSTRINGFMT<Args...> fmt, Args&&... args)
    {
        bool bShouldLog = false;
        bool bShouldColor = false;

        switch (verbosity)
        {
        case Verbosity::Fatal:
        case Verbosity::Error:
        case Verbosity::Warning:
            bShouldLog = true;
            bShouldColor = bVTSupported;
            break;
        case Verbosity::Log:
#if defined(LOGGING) && LOGGING >= 1
            bShouldLog = true;
#endif
            break;
        case Verbosity::Verbose:
#if defined(LOGGING) && LOGGING >= 2
            bShouldLog = true;
#endif
            break;
        }

        if (!bShouldLog)
        {
            return;
        }

        auto msg = std::format(fmt, std::forward<Args>(args)...);

        GENCSTR catStr = CategoryToString(category);
        GENCSTR verbStr = VerbosityToString(verbosity);

        auto now = GetCurrentTimePoint();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

        std::time_t t = std::chrono::system_clock::to_time_t(now);
        std::tm localTime{};
#ifdef PLATFORM_WINDOWS
        localtime_s(&localTime, &t);
#endif

        std::array<GENCHAR, 32> timestamp{};
        std::format_to(timestamp.data(),
            GENTEXT("[{:04}.{:02}.{:02}-{:02}.{:02}.{:02}:{:03}]"),
            localTime.tm_year + 1900,
            localTime.tm_mon + 1,
            localTime.tm_mday,
            localTime.tm_hour,
            localTime.tm_min,
            localTime.tm_sec,
            ms.count());
        
        std::array<GENCHAR, 16> ansiColor{};
        std::array<GENCHAR, 16> ansiReset{};

        if (bShouldColor)
        {
            int colorCode = VerbosityToColor(verbosity);

            std::format_to(ansiColor.data(), GENTEXT("\x1B[{}m"), colorCode);
            std::format_to(ansiReset.data(), GENTEXT("\x1B[0m"));
        }

        GENSTRING localBuffer = std::format(GENTEXT("{}  {}{}{}: {}{}\n"),
            timestamp.data(),
            ansiColor.data(),
            verbStr,
            catStr,
            msg.data(),
            ansiReset.data());

        {
            std::lock_guard<std::mutex> lock(logMutex_);
            MessageNotify::SendString(localBuffer.c_str());
        }
    }

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

private:
    static GENCSTR CategoryToString(Category cat)
    {
        switch (cat)
        {
        case Category::Application: return GENTEXT("LogApp");
        case Category::Core:        return GENTEXT("LogCore");
        case Category::Gameplay:    return GENTEXT("LogGameplay");
        case Category::Renderer:    return GENTEXT("LogRenderer");
        default:                    return GENTEXT("LogUnknown");
        }
    }

    static GENCSTR VerbosityToString(Verbosity verb)
    {
        switch (verb)
        {
        case Verbosity::Fatal:   return GENTEXT("[FATAL]    ");
        case Verbosity::Error:   return GENTEXT("[ERROR]    ");
        case Verbosity::Warning: return GENTEXT("[WARNING]  ");
        case Verbosity::Log:     return GENTEXT("           ");
        case Verbosity::Verbose: return GENTEXT("[VERBOSE]  ");
        default:                 return GENTEXT("");
        }
    }

    static int VerbosityToColor(Verbosity verb)
    {
        switch (verb)
        {
        case Verbosity::Fatal:
        case Verbosity::Error:   return 31; // red
        case Verbosity::Warning: return 33; // yellow
        default:                 return 0;  // reset
        }
    }
};

#define LOG(Cat, Fmt, ...) \
    Logger::Get().log(Cat, Verbosity::Log, GENTEXT(Fmt), __VA_ARGS__)

#define LOG_VERBOSE(Cat, Fmt, ...) \
    Logger::Get().log(Cat, Verbosity::Verbose, GENTEXT(Fmt), __VA_ARGS__)

#define CRASH_FATAL(Cat, Fmt, ...) \
    do { \
        Logger::Get().log(Cat, Verbosity::Fatal, GENTEXT(Fmt), __VA_ARGS__); \
        std::abort(); \
    } while(0)

#define LOG_ERROR(Cat, Fmt, ...) \
    Logger::Get().log(Cat, Verbosity::Error, GENTEXT(Fmt), __VA_ARGS__)

#define LOG_WARNING(Cat, Fmt, ...) \
    Logger::Get().log(Cat, Verbosity::Warning, GENTEXT(Fmt), __VA_ARGS__)
