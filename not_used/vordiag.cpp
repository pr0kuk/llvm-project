#include "libs.hpp"
#include "point.hpp"
#include "vordiag.hpp"

Point Vordiag::right()
{
    int n = points.size();
    Point max_point = Point(WIDTH+1, -1);
    for (auto i : points)
        if (i.x < max_point.x)
            max_point = i;
    return max_point;
}

Point Vordiag::left()
{
    int n = points.size();
    Point max_point = Point(-1, -1);
    for (auto i : points)
        if (i.x > max_point.x)
            max_point = i; 
    return max_point;
}