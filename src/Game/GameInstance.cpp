#include "GameInstance.h"

void GameInstance::Start()
{
    LOG(ENGINE, "Starting engine...");
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
    LOG(ENGINE, "Closing engine...");
}