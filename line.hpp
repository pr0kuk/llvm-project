#pragma once
#include "libs.hpp"
#include "point.hpp"
//#include "vorcel.hpp"
class Line
{
    public:
        Point first;
        Point second;
        Line();
        Line(Point&, Point&);
        Line(Pixel&, Point&);
};