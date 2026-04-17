#pragma once

#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>

// Singlecast Delegate
template <typename Sig>
class TDelegate;

template <typename RetVal, typename... Params>
class TDelegate<RetVal(Params...)>
{
    using FuncType = std::function<RetVal(Params...)>;
public:
    void BindLambda(FuncType func) { callback = std::move(func); }
    void Unbind() { callback = nullptr; }
    bool IsBound() const { return (bool)callback; }

    RetVal Execute(Params... args) const
    {
        return callback(std::forward<Params>(args)...);
    }

    bool ExecuteIfBound(Params... args) const
    {
        if (callback) { callback(std::forward<Params>(args)...); return true; }
        return false;
    }

private:
    FuncType callback;
};

// Multicast delegate
struct FDelegateHandle
{
    size_t id = 0;
    bool IsValid() const { return id != 0; }
};

template <typename Sig>
class TMulticastDelegate;

template <typename... Params>
class TMulticastDelegate<void(Params...)>
{
    using FDelegate = TDelegate<void(Params...)>;

    struct Entry { FDelegateHandle Handle; FDelegate Delegate; };

public:
    FDelegateHandle Add(FDelegate delegate)
    {
        FDelegateHandle handle{ ++nextId };
        entries.push_back({ handle, std::move(delegate) });
        return handle;
    }

    template <typename FunctorType>
    FDelegateHandle AddLambda(FunctorType&& functor)
    {
        FDelegate d;
        d.BindLambda(std::forward<FunctorType>(functor));
        return Add(std::move(d));
    }

    bool Remove(FDelegateHandle handle)
    {
        auto it = std::remove_if(entries.begin(), entries.end(),
            [&](const Entry& e) { return e.Handle.id == handle.id; });
        bool found = (it != entries.end());
        entries.erase(it, entries.end());
        return found;
    }

    void Clear() { entries.clear(); }

    bool IsBound() const { return !entries.empty(); }

    void Broadcast(Params... args) const
    {
        auto snapshot = entries;
        for (auto it = snapshot.rbegin(); it != snapshot.rend(); ++it)
            it->Delegate.ExecuteIfBound(args...);
    }

private:
    std::vector<Entry> entries;
    size_t nextId = 0;
};

#define DECLARE_DELEGATE(Name) \
    typedef TDelegate<void()> Name;

#define DECLARE_DELEGATE_RetVal(RetVal, Name) \
    typedef TDelegate<RetVal()> Name;

#define DECLARE_DELEGATE_OneParam(Name, P1) \
    typedef TDelegate<void(P1)> Name;

#define DECLARE_DELEGATE_TwoParams(Name, P1, P2) \
    typedef TDelegate<void(P1, P2)> Name;

#define DECLARE_DELEGATE_ThreeParams(Name, P1, P2, P3) \
    typedef TDelegate<void(P1, P2, P3)> Name;

#define DECLARE_MULTICAST_DELEGATE(Name) \
    typedef TMulticastDelegate<void()> Name;

#define DECLARE_MULTICAST_DELEGATE_OneParam(Name, P1) \
    typedef TMulticastDelegate<void(P1)> Name;

#define DECLARE_MULTICAST_DELEGATE_TwoParams(Name, P1, P2) \
    typedef TMulticastDelegate<void(P1, P2)> Name;

#define DECLARE_MULTICAST_DELEGATE_ThreeParams(Name, P1, P2, P3) \
    typedef TMulticastDelegate<void(P1, P2, P3)> Name;