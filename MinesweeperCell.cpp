//
// Created by Shira on 02.05.2024.
//

#include "MinesweeperCell.h"

MinesweeperCell::MinesweeperCell(int2 position, bool isBomb) : m_Position(position), m_isBomb(isBomb)
{}


MinesweeperCell::MinesweeperCell()
= default;

int2 MinesweeperCell::GetPosition() {
    return m_Position;
}

bool MinesweeperCell::IsBomb() const {
    return m_isBomb;
}

bool MinesweeperCell::IsRevealed() const {
    return m_Revealed;
}

bool MinesweeperCell::IsFlagged() const {
    return m_Flagged;
}

std::ostream& operator<<(std::ostream &os, MinesweeperCell &cell) {
    if(!cell.m_Revealed)
    {
        if(cell.m_Flagged)
        {
            return os << "F ";
        }
        else
        {
            return os << ". ";
        }
    }
    else if(cell.IsBomb())
    {
        return os << "X ";
    }
    else if(cell.m_NeighborBombCount == 0)
    {
        return os << "  ";
    }
    else
    {
        return os << cell.m_NeighborBombCount << " ";
    }
}



