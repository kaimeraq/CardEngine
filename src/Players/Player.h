#pragma once

class Player
{
protected:
    int m_index = -1; // Could be GUID

public:
    Player() = default;
    Player(int index);
};