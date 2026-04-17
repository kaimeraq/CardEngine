#include "GameState.h"

#include <cassert>

bool GameState::AddPlayer(int index)
{
    assert(index >= 0 && index < MAX_NUM_PLAYERS);
    
    if (m_playerOccupied[index])
    {
        return false;
    }
    
    m_players[index] = std::make_unique<Player>(index);
    m_playerOccupied[index] = true;

    return true;
}

const Player& GameState::GetPlayer(int index) const
{
    assert(index >= 0 && index < MAX_NUM_PLAYERS);
    return *m_players[index];
}

bool GameState::HasScore(int index) const
{
    assert(index >= 0 && index < MAX_NUM_PLAYERS);
    return m_scoreRecorded[index];
}

int GameState::GetScore(int index) const
{
    assert(index >= 0 && index < MAX_NUM_PLAYERS);
    
    if (!HasScore(index))
    {
        return 0;
    }

    return m_scores[index];
}

bool GameState::RecordScore(int index, int score)
{
    assert(index >= 0 && index < MAX_NUM_PLAYERS);
    
    if (HasScore(index))
    {
        return false;
    }
    
    m_scores[index] = score;
    m_scoreRecorded[index] = true;

    return true;
}