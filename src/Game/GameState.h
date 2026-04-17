#pragma once

#include "Core/CoreMinimal.h"
#include "Players/Player.h"

#include <array>

class GameState
{
protected:
    std::array<std::unique_ptr<Player>, MAX_NUM_PLAYERS> m_players{};
    std::array<bool, MAX_NUM_PLAYERS> m_playerOccupied{};

    std::array<int, MAX_NUM_PLAYERS> m_scores{};
    std::array<bool, MAX_NUM_PLAYERS> m_scoreRecorded{};

public:
    virtual bool AddPlayer(int index);
    const Player& GetPlayer(int index) const;

    bool HasScore(int index) const;
    int GetScore(int index) const;
    bool RecordScore(int index, int score);
};