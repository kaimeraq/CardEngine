#include "Player.h"

#include "Core/Config.h"

#include <print>

Player::Player(int index)
    : m_index(index)
{
#if defined(LOGGING_VERBOSE) && LOGGING_VERBOSE
    std::println("Created player {}", m_index);
#endif
}

void Player::AddCard(const CardInstance card)
{
    m_hand.AddCard(card);
}

int Player::GetHandValue() const
{
    return m_hand.SumHand();
}

const Hand& Player::GetHand() const
{
    return m_hand;
}