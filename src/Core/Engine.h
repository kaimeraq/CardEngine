#pragma once

#include <chrono>
#include <ctime>

std::time_t GetCurrentTimeSeconds();
std::chrono::system_clock::time_point GetCurrentTimePoint();