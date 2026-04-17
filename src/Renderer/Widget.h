#pragma once

class Widget
{
public:
    Widget() = default;
    virtual ~Widget() = default;

    virtual void Draw() const {}
};