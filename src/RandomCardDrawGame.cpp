#include "Game/GameInstance.h"
#include "Renderer/Widgets/CardWidget.h"
#include "Platform/Windows/Renderer/ConsoleRenderer.h"

#include <print>
#include <iostream>
#include <string>

#if defined(_WIN32) || defined(_WIN64)
#include <fcntl.h>
#include <io.h>
#include <Windows.h>
#define PLATFORM_WINDOWS
#endif

static size_t s_allocationCount = 0;

void* operator new(size_t size)
{
    ++s_allocationCount;
    return malloc(size);
}

void* operator new[](size_t size)
{
    ++s_allocationCount;
    return malloc(size);
}

// Renderer baseline allocations = 0
// Single card render allocations = 12
// Hand render allocations = 12
// Deck render allocations = 12
// Printing render allocations = 10 per
int main()
{
    ConsoleRenderer renderer;
    Deck deck;

    //deck.ShuffleDeck();

    /*Hand hand;
    deck.ShuffleDeck();

    for (int i = 0; i < MAX_NUM_CARDS_HAND; i++)
    {
        CardInstance instance = *deck.Draw();
        instance.attrib.multiplierValue = MAX_NUM_CARDS_HAND - i;
        hand.AddCard(instance);
    }

    HandWidget handWidget(&hand, &renderer);
    handWidget.Draw();*/

    //DeckWidget DeckWidget(&deck, &renderer);
    //DeckWidget.Draw();

    /*Card MyCard(Card::FaceIndex(12), Card::SuitIndex(2));

    CardWidget CardWidget(&MyCard, &renderer);
    CardWidget.Draw();*/

    //int sum = 0;
    //renderer.Println("\nScore: 0");
    
    //renderer.Println("\nAllocations: {}", s_allocationCount);
    //renderer.Println("\nAllocations: {}", s_allocationCount);
    //renderer.Println("\nAllocations: {}", s_allocationCount);
    //renderer.Println("\nAllocations: {}", s_allocationCount);
    //renderer.Println("\nAllocations: {}", s_allocationCount);
    //renderer.Println("\nAllocations: {}", s_allocationCount);
    //renderer.Println("\nAllocations: {}", s_allocationCount);
    //renderer.WaitForRender();

    //std::wstring msg = L"\nAllocations: " + std::to_wstring(s_allocationCount) + L'\n';
    //HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    //DWORD written;
    //WriteConsoleW(hOut, msg.c_str(), static_cast<DWORD>(msg.size()), &written, nullptr);

    //std::cout << "Num of allocations: " << s_allocationCount;

    //return 0;

    while (true)
    {
        Hand hand;
        deck.ShuffleDeck();

        int sum = 0;

        for (int i = 0; i < MAX_NUM_CARDS_HAND; i++)
        {
            CardInstance instance = *deck.Draw();
            instance.attrib.multiplierValue = MAX_NUM_CARDS_HAND - i;
            hand.AddCard(instance);
        }

        sum = hand.SumHand();

        HandWidget handWidget(&hand, &renderer);
        handWidget.Draw();

        renderer.Println("\nScore: {}", sum);

        for (int i = 0; i < hand.GetCardCount(); i++)
        {
            deck.Put(&hand.GetCards()[i]);
        }
        
        char choice;
        renderer.Print("\nPlay Again? (Y/N): ");
        std::cin >> choice;
        renderer.Println("");

        if (choice != 'Y' && choice != 'y')
        {
            renderer.Println("Allocations: {}", s_allocationCount);
            return 0;
        }
    }

    //GameInstance instance;
    //instance.Run();
}