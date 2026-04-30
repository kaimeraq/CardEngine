#pragma once

#include "Core/CoreMinimal.h"
#include "GameMode.h"
#include "Renderer/Renderer.h"

class GameInstance
{
    bool Tick();
    void Run();

protected:
    std::unique_ptr<Renderer> m_renderer;
    std::unique_ptr<GameMode> m_mode;
    int m_numPlayers = 0;
    
    virtual void OnInit() {};
    virtual bool OnTick() { return false; };
    virtual std::unique_ptr<GameMode> CreateMode() = 0;

public:
    explicit GameInstance(std::unique_ptr<Renderer> renderer)
        : m_renderer(std::move(renderer)) {}

    ~GameInstance() = default;
    void Start();
};