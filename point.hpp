#pragma once
#include <utility>
//#include "vorcel.hpp"
class Point
{
    public:
        int x = -1;
        int y = -1;
        //Vorcell cell;
        std::pair<int, int> get_cord();
        int set_cord(int , int);
        Point();
        Point(int, int);
};