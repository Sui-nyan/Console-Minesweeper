//
// Created by Shira on 24.04.2024.
//

#pragma once

#include <iostream>

struct int2
{
    int x;
    int y;

    int2();
    int2(int _x, int _y);

    int2 operator+(int2 val);
    int2 operator-(int2 val);
    int2 operator*(int2 val);
    int2 operator/(int2 val);

    int2 operator*=(int2 val);
    int2 operator*=(int val);

    int2 operator+=(int2 val);
    int2 operator-=(int2 val);

    friend std::ostream& operator<<(std::ostream &os, int2& val);
};
