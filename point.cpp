#include "libs.hpp"
#include "point.hpp"

std::pair<int, int> Point::get_cord() {
    return std::make_pair(x, y);
}

int Point::set_cord(int a, int b) {
    x = a;
    y = b;
    return 0;
}

Point::Point()
{
    x = -1;
    y = -1;
}

Point::Point(int a, int b)
{
    x = a;
    y = b;
}

bool operator == (Point a, Point b)
{
    return (a.x == b.x && a.y == b.y);
}

bool operator != (Point a, Point b)
{
    return (a.x != b.x || a.y != b.y);
}