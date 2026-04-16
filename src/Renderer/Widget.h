#pragma once

#include "Renderer.h"

class Widget
{
    Renderer* m_renderer = nullptr;

protected:
    Renderer* GetRenderer() const { return m_renderer; }

public:
    Widget() = default;
    Widget(Renderer* renderer) : m_renderer(renderer) {}
    virtual ~Widget() = default;

    virtual void Draw() const {}
};