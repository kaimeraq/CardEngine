#include "pch.h"
#include "GameInstance.h"

constexpr Category Cat_Game = Category::Gameplay;

void GameInstance::Start()
{
    LOG(Cat_Game, "Starting engine...");
    Run();
}

bool GameInstance::Tick()
{
    return OnTick();
}

void GameInstance::Run()
{
    OnInit();
    while (Tick());
    LOG(Cat_Game, "Closing engine...");
}