#include "libs.hpp"
#include "point.hpp"
#include "line.hpp"
#include "vordiag.hpp"
#include "vorline.hpp"
#include "pixel.hpp"
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





int lcross(Line line1, Line line2)
{
    return (line1.second.x-line1.first.x)*(line2.second.y-line2.first.y)-(line1.second.y-line1.first.y)*(line2.second.x-line2.first.x);
}

int ldot(Line line1, Line line2)
{
    return (line1.second.x-line1.first.x)*(line2.second.x-line2.first.x)+(line1.second.y-line1.first.y)*(line2.second.y-line2.first.y);
}
int dist(Point a, Point b)
{
    Line t(a, b);
    return ldot(t, t);
}

// 2 5 0 0

// 0 7    2 5
// 2*2+(-2)*(-2)

Line upper_bound(Vordiag l_vect, Vordiag r_vect) // !!!!!!!should be added uppering
{
    Point u = l_vect.right(), v = r_vect.left();
    Line perp = Line(Point(u.y-v.y, v.x-u.x), Point());
    int flagl = 1, flagr = 1;
    while (flagl == 1 || flagr == 1) {
        flagl = 0, flagr = 0;
        for (auto i = l_vect.points.begin(); i < l_vect.points.end(); i++) {
            if (ldot(perp, Line(u, *i)) > 0) {
                u = *i;
                i = l_vect.points.begin();
                flagl = 1;
            }
        }
        for (auto i = r_vect.points.begin(); i < r_vect.points.end(); i++) {
            if (ldot(perp, Line(*i, v)) > 0) {
                v = *i;
                i = r_vect.points.begin();
                flagr = 1;
            }
        }
    }
    return Line(u, v);
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
    if (lcross(line1, line2) != 0) { // not parallel
        return Point();
    }
    else { // parallel
        if (lcross(Line(line1.first, line2.second), Line(line1.second, line2.first))  != 0) { // not the same
                int a1 = line1.first.y - line1.second.y;
                int b1 = line1.first.x - line1.second.x;
                int c1 = line1.first.x * line1.second.y - line1.second.x * line1.first.y;
                int a2 = line2.first.y - line2.second.y;
                int b2 = line2.first.x - line2.second.x;
                int c2 = line2.first.x * line2.second.y - line2.second.x * line2.first.y;
                int det = a1 * b2 - a2 * b1;
                int x = (b1 * c2 - b2 * c1) / det;
                int y = (a2 * c1 - a1 * c2) / det;
                return Point(x, y);
        }
        else { // the same
            return Point(); // !!!!!!!!!!!!!!!!!!!!!!!!!!!!
        }
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
        if (perl.y < perr.y) {
            per = perl;
            //otr.first = smezh_point.get_cord(); !!!!!!!!!!!!!!!!!!!!!
        }
        else {
            per = perr;
            //otr.second = smezh_point.get_cord(); !!!!!!!!!!!!!!!!!!!!!
        }
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
    int n = 4;
    std::vector<Point> points(n);
    points[0].x = 2;
    points[1].x = 5;
    points[2].x = 7;
    points[3].x = 9;

    points[0].y = 5;
    points[1].y = 5;
    points[2].y = 3;
    points[3].y = 9;
    std::vector<std::vector<Pixel>> pixels(HEIGHT, std::vector<Pixel>(WIDTH));
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            int maxd = 1000000;
            pixels[i][j].x = j;
            pixels[i][j].y = i;
            Point t(j, i);
            for (int k = 0; k < n; k++) {
                //std::cout << points[k].x << " " << points[k].y << " " << i << " " << j << " " << dist(t, points[k]) << std::endl;
                if (dist(t, points[k]) < maxd) {
                    maxd = dist(t, points[k]);
                    pixels[i][j].color = k;
                    if (maxd == 0) {
                        pixels[i][j].color = 9;
                        break;
                    }
                }
            }
        }
    }
    //std::cout << std::endl << std::endl;

    for (int i = HEIGHT - 1; i >= 0; i--) {
        for (int j = 0; j < WIDTH; j++) {
            std::cout << pixels[i][j].color << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}