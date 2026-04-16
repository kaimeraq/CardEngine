#include "GameState.h"

#include <cassert>

bool GameState::AddPlayer(int index)
{
    assert(index >= 0 && index < MAX_NUM_PLAYERS);
    
    if (m_playerOccupied[index])
    {
        return false;
    }
    
    m_players[index] = Player(index);
    m_playerOccupied[index] = true;

    return true;
}

void GameState::DealCardToPlayer(int index)
{
    assert(index >= 0 && index < MAX_NUM_PLAYERS);
    m_players[index].AddCard(*m_deck.Draw());
}

void GameState::ShuffleDeck()
{
    m_deck.ShuffleDeck();
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

bool GameState::RecordScore(int index)
{
    assert(index >= 0 && index < MAX_NUM_PLAYERS);
    
    if (HasScore(index))
    {
        return false;
    }
    
    m_scores[index] = m_players[index].GetHandValue();
    m_scoreRecorded[index] = true;

    return true;
}

const Hand& GameState::GetPlayerHand(int index) const
{
    assert(index >= 0 && index < MAX_NUM_PLAYERS);
    return m_players[index].GetHand();
}