#pragma once

#include "Core/CoreMinimal.h"
#include "GameState.h"

class GameMode
{
protected:
    std::unique_ptr<GameState> m_state;
    int m_numPlayers = 0;

    explicit GameMode(int playerAmt, std::unique_ptr<GameState> state)
        : m_state(std::move(state))
    {
        m_numPlayers = playerAmt < MAX_NUM_PLAYERS ? playerAmt : MAX_NUM_PLAYERS;
    }

public:
    virtual ~GameMode() = default;
    GameMode(const GameMode&) = delete;
    GameMode& operator=(const GameMode&) = delete;

    virtual void BeginPlay() {};
};