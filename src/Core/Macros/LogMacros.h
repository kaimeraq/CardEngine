#pragma once

#include "Core/Logger.h"

#define LOG(Cat, Fmt, ...) \
    Logger::Get().log(Cat, Verbosity::Log, GENTEXT(Fmt), __VA_ARGS__)

#define LOG_VERBOSE(Cat, Fmt, ...) \
    Logger::Get().log(Cat, Verbosity::Verbose, GENTEXT(Fmt), __VA_ARGS__)

#define LOG_ERROR(Cat, Fmt, ...) \
    Logger::Get().log(Cat, Verbosity::Error, GENTEXT(Fmt), __VA_ARGS__)

#define LOG_WARN(Cat, Fmt, ...) \
    Logger::Get().log(Cat, Verbosity::Warning, GENTEXT(Fmt), __VA_ARGS__)