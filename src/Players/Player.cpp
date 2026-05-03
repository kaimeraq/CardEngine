#include "Player.h"

#include "Core/CoreMinimal.h"

constexpr Category Cat_Game = Category::Gameplay;

Player::Player(int index)
    : m_index(index)
{
    LOG_VERBOSE(Cat_Game, "Created player {}", m_index);
}