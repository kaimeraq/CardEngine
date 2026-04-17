#pragma once

#include "Core/CoreMinimal.h"
#include "GameState.h"

class GameMode
{
protected:
    int m_numPlayers = 0;
    std::unique_ptr<GameState> m_state;

public:
    GameMode(int playerAmt)
        : m_state(std::make_unique<GameState>()) 
    {
        m_numPlayers = playerAmt < MAX_NUM_PLAYERS ? playerAmt : MAX_NUM_PLAYERS;
    }

    virtual void BeginPlay() {};
};