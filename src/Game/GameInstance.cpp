#include "GameInstance.h"

#include "Core/Config.h"

#include <iostream>
#include <print>

void GameInstance::PrintResult() const
{
    if (m_result.numWinners > 1)
    {
        std::print("It's a tie between players ");

        for (int i = 0; i < m_result.numWinners; i++)
        {
            if (i == m_result.numWinners - 1)
            {
                std::print("{}", m_result.winners[i]);
            }
            else if (i == m_result.numWinners - 2 && m_result.numWinners == 2)
            {
                std::print("{} and ", m_result.winners[i]);
            }
            else if (i == m_result.numWinners - 2)
            {
                std::print("{}, and ", m_result.winners[i]);
            }
            else
            {
                std::print("{}, ", m_result.winners[i]);
            }
        }

        std::println(" with a score of {}", m_result.winningScore);
    }
    else
    {
        std::println("Player {} wins with a score of {}!", m_result.winnerID, m_result.winningScore);
    }

    // Debug print winning hand
#if defined(LOGGING_VERBOSE) && LOGGING_VERBOSE
    m_result.query->GetPlayerHand(m_result.winnerID).LogHand();
#endif
}

bool GameInstance::Tick()
{
    switch (m_state)
    {
    case GameLoopState::SELECT:
    {
        std::print("Number of players? (2-{}): ", MAX_NUM_PLAYERS);
        std::cin >> m_numPlayers;

        if (!std::cin)
        {
            return false;
        }

        if (m_numPlayers >= 2 && m_numPlayers <= MAX_NUM_PLAYERS)
        {
            m_state = GameLoopState::PLAYING;
        }

        break;
    }
    case GameLoopState::PLAYING:
    {
        m_game = GameMode(m_numPlayers);
        m_result = m_game.Play();
        m_state = GameLoopState::RESULTS;
        break;
    }
    case GameLoopState::RESULTS:
    {
        PrintResult();
        m_state = GameLoopState::REPLAY;
        break;
    }
    case GameLoopState::REPLAY:
    {
        char choice;
        std::print("\nPlay Again? (Y/N): ");
        std::cin >> choice;
        std::println();

        if (choice == 'Y' || choice == 'y')
        {
            m_state = GameLoopState::SELECT;
        }
        else
        {
            return false;
        }

        break;
    }
    }

    return true;
}

void GameInstance::Run()
{
    while (Tick());
}