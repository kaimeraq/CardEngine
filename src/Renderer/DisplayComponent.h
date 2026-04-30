#pragma once

class DisplayComponent
{
public:
    virtual ~DisplayComponent() = default;
protected:
    virtual void OnPreDisplay() {}
    virtual void OnPostDisplay() {}
	virtual void OnDisplay() = 0;

    void Display()
    {
        OnPreDisplay();
        OnDisplay();
        OnPostDisplay();
    }
};