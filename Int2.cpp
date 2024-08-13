//
// Created by Shira on 24.04.2024.
//

#include "Int2.h"

int2::int2() : x(0), y(0)
{}

int2::int2(int _x, int _y) : x(_x), y(_y)
{}

int2 int2::operator+(int2 val) {
    return {x+val.x, y+val.y};
}

int2 int2::operator-(int2 val) {
    return {x-val.x, y-val.y};
}

int2 int2::operator*(int2 val) {
    return {x*val.x, y*val.y};
}

int2 int2::operator/(int2 val) {
    return {x/val.x, y/val.y};
}

int2 int2::operator*=(int2 val) {
    return {x*val.x, y*val.y};
}

int2 int2::operator*=(int val) {
    return {x*val, y*val};
}

int2 int2::operator+=(int2 val) {
    return {x+val.x, y+val.y};
}

int2 int2::operator-=(int2 val) {
    return {x-val.x, y-val.y};
}

std::ostream &operator<<(std::ostream &os, int2 &val) {
    return os << "(" << val.x << "|" << val.y << ")";
}
