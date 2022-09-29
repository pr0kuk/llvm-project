#pragma once
#include "libs.hpp"
#include "pixel.hpp"
//#include "vorcel.hpp"
class Point
{
    public:
        int x = -1;
        int y = -1;
        std::vector<Pixel> refpixels;
        //Vorcell cell;
        std::pair<int, int> get_cord();
        int set_cord(int , int);
        Point();
        Point(int, int);
};