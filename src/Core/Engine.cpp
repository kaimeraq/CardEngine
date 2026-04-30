#include "Engine.h"

std::time_t GetCurrentTimeSeconds()
{
    auto now = std::chrono::system_clock::now();
    return std::chrono::system_clock::to_time_t(now);
}

std::chrono::system_clock::time_point GetCurrentTimePoint()
{
    return std::chrono::system_clock::now();
}