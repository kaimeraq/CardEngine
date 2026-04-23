#pragma once

#include "Platform/Platform.h"
#include <cstdarg>

class Logger {
public:
    static Logger& Get() {
        static Logger instance;
        return instance;
    }

    template<typename... Args>
    void log(const char* category, std::wformat_string<Args...> fmt, Args&&... args)
    {
        auto msg = std::format(fmt, std::forward<Args>(args)...);

        swprintf(staticBuffer_,
            sizeof(staticBuffer_) / sizeof(GENCHAR),
            TEXT("[%hs] %ls\n"),
            category,
            msg.c_str());

        MessageNotify::SendString(staticBuffer_);
    }

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

private:
    Logger() {}
    inline static GENCHAR staticBuffer_[4096];
};

#define LOG(Category, Fmt, ...) \
    Logger::Get().log(#Category, TEXT(Fmt), __VA_ARGS__)