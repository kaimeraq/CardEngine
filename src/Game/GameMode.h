#pragma once

#include "GameState.h"

#include "IGameQuery.h"

class GameMode
{
    int m_numPlayers;
    GameState m_state;

public:
    GameMode(int playerAmt): m_numPlayers(playerAmt) {}

    GameResult Play();
};