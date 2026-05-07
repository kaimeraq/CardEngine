#pragma once

class Renderer
{
protected:
    virtual void Flush() {}
    virtual void Clear() {}

    static void SetInstance(Renderer* instance) 
    {
        s_instance = instance;
    }

public:
    static Renderer& Get() 
    {
        return *s_instance;
    }

    template<typename T>
    T* As()
    {
        return dynamic_cast<T*>(this);
    }

    virtual ~Renderer() = default;

private:
    static inline Renderer* s_instance = nullptr;
};