cmake_minimum_required(VERSION 3.27)
project(exc4)

set(CMAKE_CXX_STANDARD 17)

add_executable(exc4
        main.cpp
        Int2.cpp
        Int2.h
        MinesweeperCell.cpp
        MinesweeperCell.h
        MinesweeperGrid.cpp
        MinesweeperGrid.h
)
