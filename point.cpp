#pragma once
#include <utility>
#include "point.hpp"

std::pair<int, int> Point::get_cord() {
    return cord;
}

int Point::set_cord(std::pair<int, int> new_cord) {
    cord = new_cord;
    return 0;
}