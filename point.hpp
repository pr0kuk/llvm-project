#pragma once
#include <utility>
#include "vorcel.hpp"
class Point
{
    private:
        std::pair<int, int> cord = std::make_pair(0,0);
    public:
        Vorcell cell;
        std::pair<int, int> get_cord();
        int set_cord(std::pair<int, int> new_cord);
};