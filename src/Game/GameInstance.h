#pragma once

#include "IGameQuery.h"
#include "GameMode.h"

class GameInstance
{
    GameLoopState m_state = GameLoopState::SELECT;
    int m_numPlayers = 0;
    GameResult m_result;
    GameMode m_game{ 0 };

    void PrintResult() const;
    bool Tick();

public:
    void Run();
};