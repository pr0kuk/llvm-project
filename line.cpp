#include "libs.hpp"
#include "point.hpp"
#include "line.hpp"

Line::Line()
{
    first = Point();
    second = Point();
}

Line::Line(Point a, Point b)
{
    first = a;
    second = b;
}