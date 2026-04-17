#include "Player.h"
#include "Core/CoreMinimal.h"

#include <print>

Player::Player(int index)
    : m_index(index)
{
#if defined(LOGGING_VERBOSE) && LOGGING_VERBOSE
    LOG(VERBOSE, "Created player {}", m_index);
#endif
}