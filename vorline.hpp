#include <utility>
#include "line.hpp"
#include "point.hpp"
class Vorline
{
    public:
        Line line;
        std::pair<Point, Point> centers;
    //public:
    //     std::vector<std::pair<std::pair<int,int>>> get_lines();
    //     int set_line();
};