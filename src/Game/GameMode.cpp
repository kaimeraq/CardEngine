#include "GameMode.h"

GameResult GameMode::Play()
{
    for (int i = 0; i < m_numPlayers; i++)
    {
        m_state.AddPlayer(i);
    }

    m_state.ShuffleDeck();

    for (int i = 0; i < m_numPlayers; i++)
    {
        for (int j = 0; j < MAX_NUM_CARDS_HAND; j++)
        {
            m_state.DealCardToPlayer(i);
        }

        m_state.RecordScore(i);
    }

    // Check for winners
    int winnerID = 0;
    std::array<int, MAX_NUM_PLAYERS> winners{};
    int numWinners = 1;
    winners[0] = 0;

    for (int i = 1; i < m_numPlayers; i++)
    {
        if (m_state.GetScore(i) > m_state.GetScore(winnerID))
        {
            winnerID = i;
            numWinners = 1;
            winners[0] = i;

        }
        else if (m_state.GetScore(i) == m_state.GetScore(winnerID))
        {
            winners[numWinners++] = i;
        }
    }

    return { &m_state, winnerID, m_state.GetScore(winnerID), winners, numWinners };
}