#pragma once

class Renderer
{
protected:
    virtual void Flush() {}
    virtual void Clear() {}

public:
    virtual ~Renderer() = default;
};