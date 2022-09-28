#pragma once
#define HEIGHT 1000
#define WIDTH 1000
#include <iostream>
#include <vector>
#include "point.hpp"
#include "line.hpp"
#include "vordiag.hpp"
#include <utility>
bool operator == (Point a, Point b);
bool operator != (Point a, Point b);
int divide(Vordiag vect, Vordiag& l_vect, Vordiag& r_vect)
{
    int n = vect.points.size();
    int n1 = n / 2;
    for (int i = 0; i < n; i++) {
        if (i < n1)
            l_vect.points.push_back(vect.points[i]);
        else
            r_vect.points.push_back(vect.points[i]);
    }
    return 0;
}

Line upper_bound(Vordiag l_vect, Vordiag r_vect) {
    Line ret;
    return ret;
}

Line serp(Line otr) {
    Line ret;
    int a = (otr.first.y-otr.second.y)/(otr.first.x-otr.second.x);
    int x0 = (otr.first.x+otr.second.x)/2;
    int y0 = (otr.first.x+otr.second.x)/2;
    int y = -WIDTH/a + x0/a + y0;
    int x = -HEIGHT * a + x0 + y0 * a;
    if (y < HEIGHT)
        ret.second = Point(WIDTH, y);
    else {
        ret.second = Point(x, HEIGHT);
    }
    return ret;
}


Point percline(Line line1, Line line2)
{
    if ((line1.second.x-line1.first.x)*(line2.second.y-line2.first.y)-(line1.second.y-line1.first.y)*(line2.second.x-line2.first.x) != 0) {
        return Point();
    }
    else {
        return Point();
    }
}

Point perc(Line srp, Vordiag vordiag, Point& smezh_point)
{
    int n = vordiag.vorlines.size();
    Point ret;
    Point check = Point();
    for (int i = 0; i < n; i++) {
        ret = percline(srp, vordiag.vorlines[i].line);
        if (ret != check)
            break;
    }
    return ret;
}


Vordiag merge(Vordiag l_vect, Vordiag r_vect)
{
    Point per, perl, perr, check = Point();
    Line srp, otr;
    otr = upper_bound(l_vect, r_vect);
    Point smezh_point = check;
    while(1) {
        srp = serp(otr);
        perl = perc(srp, l_vect, smezh_point);
        perr =  perc(srp, r_vect, smezh_point);
        if (perl == check && perr == check)
            break;
       /* if (perl < perr) { !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            per = perl;
            //otr.first = smezh_point.get_cord(); !!!!!!!!!!!!!!!!!!!!!
        }
        else {
            per = perr;
            //otr.second = smezh_point.get_cord(); !!!!!!!!!!!!!!!!!!!!!
        }!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
    }
    Vordiag m_vect = l_vect; // !!!!!!!!!!!!!!!!!!!!!
    return m_vect;
}


Vordiag iter(Vordiag vect)
{
    Vordiag l_vect, r_vect;
    divide(vect, l_vect, r_vect);
    if (l_vect.vorlines.size() > 1)
        iter(l_vect);
    if (r_vect.vorlines.size() > 1)
        iter(r_vect);
    Vordiag m_vect = merge(l_vect, r_vect);
    return m_vect;
}




int main()
{
    std::vector<Point> points(16);
    return 0;
}