#pragma once

class Renderer
{
protected:
    virtual void OnPreDisplay() {}
    virtual void OnPostDisplay() {}
    virtual void OnDisplay() = 0;
    virtual void Flush() {}
    virtual void Clear() {}

public:
    void Display()
    {
        OnPreDisplay();
        OnDisplay();
        OnPostDisplay();
    }

    virtual ~Renderer() = default;
};