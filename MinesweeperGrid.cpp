//
// Created by Shira on 02.05.2024.
//

#include "MinesweeperGrid.h"
#include <iostream>
#include <random>
#include <algorithm>

using namespace std;

MinesweeperGrid::MinesweeperGrid(unsigned int width, unsigned int height, float bombsPercentage) : m_Width(width), m_Height(height), m_BombsPercentage(bombsPercentage)
{
    InitializeCells();
}

void MinesweeperGrid::InitializeCells() {
    m_MaxBombCount = m_Width * m_Height * m_BombsPercentage;
    int currBombCount = 0;

    random_device rd; // obtain a random number from hardware
    mt19937 gen(rd()); // seed the generator

    uniform_int_distribution<> distr(0, 99);

    for (int y = 0; y < m_Height; y++) {
        for (int x = 0; x < m_Width; x++) {
            auto it = m_Values.end();
            MinesweeperCell cell;
            if(currBombCount < m_MaxBombCount && distr(gen) <= m_BombsPercentage * 100) {
                cell = MinesweeperCell(int2(x,y), true);
                currBombCount++;
            } else {
                cell = MinesweeperCell(int2(x,y), false);
            }

            m_Values.insert(it, cell);
        }
    }

    for (int i = 0; i < m_Values.size(); ++i) {
        int2 location = GetLocationFromIndex(i);

        if(!m_Values[i].IsBomb())
            m_Values[i].m_NeighborBombCount = CalculateNeighboringBombsCount(location);
    }
}

int MinesweeperGrid::CalculateNeighboringBombsCount(int2 location) {
    int bombCount = 0;
    for (int y = location.y-1; y <= location.y+1 ; y++) {
        for (int x = location.x-1; x <= location.x+1; x++) {
            if(LocationInBounds(int2(x,y))){
                if(IsBomb(int2(x,y))){
                    bombCount++;
                }
            }
        }
    }
    return bombCount;
}

bool MinesweeperGrid::IsBomb(unsigned int index) const {
    return m_Values[index].IsBomb();
}

bool MinesweeperGrid::IsBomb(int2 location) const {
    return m_Values[GetIndexFromLocation(location)].IsBomb();
}

bool MinesweeperGrid::IsRevealed(int2 location) const {
    return m_Values[GetIndexFromLocation(location)].IsRevealed();
}

bool MinesweeperGrid::IsFlagged(int2 location) const {
    return m_Values[GetIndexFromLocation(location)].IsFlagged();
}

int MinesweeperGrid::GetNeighborBombCount(unsigned int index) const {
    return m_Values[index].m_NeighborBombCount;
}

int MinesweeperGrid::GetNeighborBombCount(int2 location) const {
    return m_Values[GetIndexFromLocation(location)].m_NeighborBombCount;
}

unsigned int MinesweeperGrid::GetIndexFromLocation(int2 location) const {
    return m_Width * location.y + location.x;
}

int2 MinesweeperGrid::GetLocationFromIndex(unsigned int index) {
    return m_Values[index].GetPosition();
}

unsigned int MinesweeperGrid::GetWidth() const {
    return m_Width;
}

unsigned int MinesweeperGrid::GetHeight() const {
    return m_Height;
}

bool MinesweeperGrid::IndexInBounds(unsigned int index) const{
    return index < m_Values.size();
}

bool MinesweeperGrid::LocationInBounds(int2 location) const {
    return location.x < m_Width && location.y < m_Height;
}

void MinesweeperGrid::PrintGrid() const {
    for (int i = 0; i <= m_Width + 1; ++i) {
        cout << "* ";
    }
    cout << endl;
    for (int y = 0; y <= m_Height; y++) {
        cout << "* ";
        for (int x = 0; x <= m_Width; x++) {
            auto pos = int2(x, y);

            if(LocationInBounds(pos)) {
                const MinesweeperCell& cell = m_Values[GetIndexFromLocation(pos)];

                //cout << cell;
                if(!cell.m_Revealed)
                {
                    if(cell.m_Flagged)
                    {
                        cout << "F";
                    }
                    else
                    {
                        cout << ".";
                    }
                }
                else if(cell.IsBomb())
                {
                    cout << "X";
                }
                else if(cell.m_NeighborBombCount == 0)
                {
                    cout << " ";
                }
                else
                {
                    cout << cell.m_NeighborBombCount;
                }

            } else {
                cout << "*";
            }
            cout << " ";
        }
        cout << "\n";
    }
}

/**
 * Reveals cell, if cell has no adjacent bombs, neighbouring cells will also be revealed.
 * Process will repeat until there are no neighbouring cells with no adjacent bombs.
 * @param location cell location
 */
void MinesweeperGrid::RevealNeighboringCellsAtLocation(int2 location) {
    if(!LocationInBounds(location) || m_Values[GetIndexFromLocation(location)].IsRevealed())
        return;

    auto &cell = m_Values[GetIndexFromLocation(location)];

    cell.m_Revealed = true;
    if(cell.IsFlagged()) {
        cell.m_Flagged = false;
        m_FlagCount -= 1;
    }

    if(cell.IsBomb())
        EndGame();

    if(GetNeighborBombCount(location) == 0) {
        int x = location.x;
        int y = location.y;
        RevealNeighboringCellsAtLocation(int2(x, y+1));
        RevealNeighboringCellsAtLocation(int2(x, y-1));
        RevealNeighboringCellsAtLocation(int2(x-1, y));
        RevealNeighboringCellsAtLocation(int2(x-1, y+1));
        RevealNeighboringCellsAtLocation(int2(x-1, y-1));
        RevealNeighboringCellsAtLocation(int2(x+1, y));
        RevealNeighboringCellsAtLocation(int2(x+1, y-1));
        RevealNeighboringCellsAtLocation(int2(x+1, y+1));
    }
    else {
        return;
    }
}
/**
 * Flags cell at given location.
 * Flagged cells will be unflaged. Revealed cells cannot be flagged
 * @param location cell location
 */
void MinesweeperGrid::FlagCellAtLocation(int2 location) {
    auto &cell = m_Values[GetIndexFromLocation(location)];
    if(!cell.IsRevealed()) {
        if(cell.IsFlagged()) {
            cell.m_Flagged = false;
            m_FlagCount += 1;
        }
        else {
            cell.m_Flagged = true;
            m_FlagCount += 1;
            cout << "Currently used flags: " << m_FlagCount << " / " << m_MaxBombCount << endl;
        }
    } else {
        cout << "You cannot flag revealed cells." << endl;
    }
}

/**
 * Checks if all non bomb cells are revealed and all bombs are flagged
 * @return
 */
bool MinesweeperGrid::CheckGameWon() {
    return all_of(m_Values.begin(), m_Values.end(),[](MinesweeperCell &cell){
        bool bombFlagged = (cell.IsBomb() && cell.IsFlagged());
        bool emptyCellRevealed = (!cell.IsBomb() && cell.IsRevealed());
        return bombFlagged || emptyCellRevealed;
    });
}

void MinesweeperGrid::EndGame() const {
    cout << "Game Lost. Landed on Mine." << endl;
    exit(0);
}

