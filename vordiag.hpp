#pragma once
#include "libs.hpp"
#include "point.hpp"
#include "vorline.hpp"
class Vordiag
{
    public:
        std::vector<Vorline> vorlines;
        std::vector<Point> points;
        Point right();
        Point left();
};