#pragma once

#include "Cards/Hand.h"

class Player
{
    int m_index = -1; // Could be GUID
    Hand m_hand;

public:
    Player() = default;
    Player(int index);

    void AddCard(const CardInstance card);
    int GetHandValue() const;
    const Hand& GetHand() const;
};