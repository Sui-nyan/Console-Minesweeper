//
// Created by Shira on 02.05.2024.
//

#pragma once
#include "Int2.h"
#include <iostream>

class MinesweeperCell
{
private:
    int2 m_Position;

public:
    MinesweeperCell(int2 position, bool isBomb);
    MinesweeperCell();

    int2 GetPosition();
    bool IsBomb() const;
    bool IsRevealed() const;
    bool IsFlagged() const;

    int m_NeighborBombCount = 0;
    bool m_Revealed = false;
    bool m_Flagged = false;

    friend std::ostream& operator<<(std::ostream &os, MinesweeperCell &cell);
private:
    bool m_isBomb = false;
};
