#pragma once

#include <functional>
#include <vector>
#include <algorithm>

// Singlecast Delegate
template <typename Sig>
class Delegate;

template <typename RetVal, typename... Params>
class Delegate<RetVal(Params...)>
{
    using FuncType = std::function<RetVal(Params...)>;
public:
    void BindLambda(FuncType func) 
    { 
        callback = std::move(func); 
    }

    void Unbind() 
    { 
        callback = nullptr; 
    }

    bool IsBound() const 
    { 
        return (bool)callback; 
    }

    bool ExecuteIfBound(Params... args) const
    {
        if (callback) 
        { 
            callback(std::forward<Params>(args)...); 
            return true; 
        }

        return false;
    }

private:
    FuncType callback;
};

// Multicast delegate
struct DelegateHandle
{
    size_t id = 0;
    
    bool IsValid() const 
    { 
        return id != 0; 
    }
};

template <typename Sig>
class MulticastDelegate;

template <typename... Params>
class MulticastDelegate<void(Params...)>
{
    using BoundDelegate = Delegate<void(Params...)>;

    struct Entry 
    { 
        DelegateHandle Handle; 
        BoundDelegate Delegate; 
    };

public:
    DelegateHandle Add(BoundDelegate delegate)
    {
        DelegateHandle handle{ ++nextId };
        entries.push_back({ handle, std::move(delegate) });

        return handle;
    }

    template <typename FunctorType>
    DelegateHandle AddLambda(FunctorType&& functor)
    {
        BoundDelegate d;
        d.BindLambda(std::forward<FunctorType>(functor));

        return Add(std::move(d));
    }

    bool Remove(DelegateHandle handle)
    {
        auto it = std::remove_if(entries.begin(), entries.end(), [&](const Entry& e) 
        { 
            return e.Handle.id == handle.id; 
        });

        bool found = (it != entries.end());
        entries.erase(it, entries.end());

        return found;
    }

    void Clear() 
    { 
        entries.clear(); 
    }

    bool IsBound() const 
    { 
        return !entries.empty(); 
    }

    void Broadcast(Params... args) const
    {
        auto snapshot = entries;
        for (auto it = snapshot.rbegin(); it != snapshot.rend(); ++it)
        {
            it->Delegate.ExecuteIfBound(args...);
        }
    }

private:
    std::vector<Entry> entries;
    size_t nextId = 0;
};

#define DELEGATE(Name) \
    typedef Delegate<void()> Name;

#define DELEGATE_RETURN(RetVal, Name) \
    typedef Delegate<RetVal()> Name;

#define DELEGATE_ONE_PARAM(Name, P1) \
    typedef Delegate<void(P1)> Name;

#define DELEGATE_TWO_PARAMS(Name, P1, P2) \
    typedef Delegate<void(P1, P2)> Name;

#define DELEGATE_THREE_PARAMS(Name, P1, P2, P3) \
    typedef Delegate<void(P1, P2, P3)> Name;

#define MULTICAST_DELEGATE(Name) \
    typedef MulticastDelegate<void()> Name;

#define MULTICAST_DELEGATE_ONE_PARAM(Name, P1) \
    typedef MulticastDelegate<void(P1)> Name;

#define MULTICAST_DELEGATE_TWO_PARAMS(Name, P1, P2) \
    typedef MulticastDelegate<void(P1, P2)> Name;

#define MULTICAST_DELEGATE_THREE_PARAMS(Name, P1, P2, P3) \
    typedef MulticastDelegate<void(P1, P2, P3)> Name;