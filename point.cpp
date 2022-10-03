#include "libs.hpp"
#include "point.hpp"

std::pair<int, int> Point::get_cord() {
    return std::make_pair(x, y);
}

void Point::set_cord(int a, int b) {
    x = a, y = b;
}

Point::Point() {
    x = 0, y = 0;
}

Point::Point(int a, int b) {
    x = a, y = b;
}

bool operator == (Point a, Point b) {
    return (a.x == b.x && a.y == b.y);
}

bool operator != (Point a, Point b) {
    return (a.x != b.x || a.y != b.y);
}