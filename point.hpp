#pragma once
#include "libs.hpp"
class Point
{
    public:
        int color;
        int x = -1;
        int y = -1;
        std::pair<int, int> get_cord();
        int set_cord(int , int);
        Point();
        Point(int, int);
};

class CenterPoint: public Point
{
        //std::vector<Pixel> refpixels;
        //Vorcell cell;
};