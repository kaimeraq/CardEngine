#pragma once

#include "Cards/Hand.h"

constexpr int MAX_NUM_PLAYERS = 4;

class IGameQuery
{
public:
    virtual const Hand& GetPlayerHand(int index) const = 0;
    virtual ~IGameQuery() = default;
};

enum class GameLoopState
{
    SELECT,
    PLAYING,
    RESULTS,
    REPLAY
};

struct GameResult
{
    const IGameQuery* query;
    int winnerID;
    int winningScore;
    std::array<int, MAX_NUM_PLAYERS> winners;
    int numWinners = 0;
};