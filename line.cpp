#include "libs.hpp"
#include "point.hpp"
#include "line.hpp"

Line::Line()
{
    first = Point();
    second = Point();
}

Line::Line(Point& a, Point& b)
{
    first = a;
    second = b;
}

Line::Line(Pixel& a, Point& b)
{
    first.x = a.x;
    first.y = a.y;
    second = b;
}