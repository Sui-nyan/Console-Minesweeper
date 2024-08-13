//
// Created by Shira on 02.05.2024.
//

#pragma once

#include <vector>
#include "MinesweeperCell.h"
#include "Int2.h"

class MinesweeperGrid
{
public:
    MinesweeperGrid(unsigned int width, unsigned int height, float bombsPercentage);

    void InitializeCells();
    int CalculateNeighboringBombsCount(int2 location);

    bool IsBomb(unsigned int index) const;
    bool IsBomb(int2 location) const;
    bool IsRevealed(int2 location) const;
    bool IsFlagged(int2 location) const;

    int GetNeighborBombCount(unsigned int index) const;
    int GetNeighborBombCount(int2 location) const;

    unsigned int GetIndexFromLocation(int2 location) const;
    int2 GetLocationFromIndex(unsigned int index);

    unsigned int GetWidth() const;
    unsigned int GetHeight() const;

    bool IndexInBounds(unsigned int index) const;
    bool LocationInBounds(int2 location) const;

    void PrintGrid() const;
    /**
     * Reveals the clicked cell.
     * If the cell has no adjacent bombs, the neighboring cells are revealed in each direction until there is an adjacent bomb.
     *
     * @param location position that has been clicked
     */
    void RevealNeighboringCellsAtLocation(int2 location);

    void FlagCellAtLocation(int2 location);

    /**
     * Checks if all Bombs are flagged and all fields are revealed.
     */
    bool CheckGameWon();

    /**
     * Reveals all Bombs on the Map.
     */
    void EndGame() const;

private:
    unsigned int m_Width = 0;
    unsigned int m_Height = 0;
    float m_BombsPercentage = 0.0f;
    int m_MaxBombCount;
    int m_FlagCount = 0;

    std::vector<MinesweeperCell> m_Values;
};
