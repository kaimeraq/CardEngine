#pragma once

#include "Players/Player.h"
#include "Cards/Deck.h"
#include "IGameQuery.h"

#include <array>

class GameState : public IGameQuery
{
    std::array<Player, MAX_NUM_PLAYERS> m_players{};
    std::array<bool, MAX_NUM_PLAYERS> m_playerOccupied{};

    std::array<int, MAX_NUM_PLAYERS> m_scores{};
    std::array<bool, MAX_NUM_PLAYERS> m_scoreRecorded{};

    Deck m_deck;

public:
    bool AddPlayer(int index);
    void DealCardToPlayer(int index);
    void ShuffleDeck();

    bool HasScore(int index) const;
    int GetScore(int index) const;
    bool RecordScore(int index);

    const Hand& GetPlayerHand(int index) const override;
};