#include "libs.hpp"
#include "point.hpp"
#include "line.hpp"
#include "vordiag.hpp"
#include "vorline.hpp"
#include<cstdlib>
#include "pixel.hpp"
// bool operator == (Point a, Point b);
// bool operator != (Point a, Point b);
// int divide(Vordiag vect, Vordiag& l_vect, Vordiag& r_vect)
// {
//     int n = vect.points.size();
//     int n1 = n / 2;
//     for (int i = 0; i < n; i++) {
//         if (i < n1)
//             l_vect.points.push_back(vect.points[i]);
//         else
//             r_vect.points.push_back(vect.points[i]);
//     }
//     return 0;
// }





// int lcross(Line line1, Line line2)
// {
//     return (line1.second.x-line1.first.x)*(line2.second.y-line2.first.y)-(line1.second.y-line1.first.y)*(line2.second.x-line2.first.x);
// }

int ldot(Line& line1, Line& line2)
{
    return (line1.second.x-line1.first.x)*(line2.second.x-line2.first.x)+(line1.second.y-line1.first.y)*(line2.second.y-line2.first.y);
}
// int dist(Point& a, Point& b)
// {
//     Line t(a, b);
//     return ldot(t, t);
// }

int ldot(Pixel& a, Point& b, Pixel& c, Point& d)
{
    return (b.x-a.x)*(d.x-c.x)+(b.y-a.y)*(d.y-c.y);
}


int dist(Pixel& a, Point& b)
{
    return (b.x-a.x)*(b.x-a.x)+(b.y-a.y)*(b.y-a.y);
    //Line t(a, b);
    //return ldot(a,b,a,b);
}

// Line upper_bound(Vordiag l_vect, Vordiag r_vect) // !!!!!!!should be added uppering
// {
//     Point u = l_vect.right(), v = r_vect.left();
//     Line perp = Line(Point(u.y-v.y, v.x-u.x), Point());
//     int flagl = 1, flagr = 1;
//     while (flagl == 1 || flagr == 1) {
//         flagl = 0, flagr = 0;
//         for (auto i = l_vect.points.begin(); i < l_vect.points.end(); i++) {
//             if (ldot(perp, Line(u, *i)) > 0) {
//                 u = *i;
//                 i = l_vect.points.begin();
//                 flagl = 1;
//             }
//         }
//         for (auto i = r_vect.points.begin(); i < r_vect.points.end(); i++) {
//             if (ldot(perp, Line(*i, v)) > 0) {
//                 v = *i;
//                 i = r_vect.points.begin();
//                 flagr = 1;
//             }
//         }
//     }
//     return Line(u, v);
// }

// Line serp(Line otr) {
//     Line ret;
//     int a = (otr.first.y-otr.second.y)/(otr.first.x-otr.second.x);
//     int x0 = (otr.first.x+otr.second.x)/2;
//     int y0 = (otr.first.x+otr.second.x)/2;
//     int y = -WIDTH/a + x0/a + y0;
//     int x = -HEIGHT * a + x0 + y0 * a;
//     if (y < HEIGHT)
//         ret.second = Point(WIDTH, y);
//     else {
//         ret.second = Point(x, HEIGHT);
//     }
//     return ret;
// }


// Point percline(Line line1, Line line2)
// {
//     if (lcross(line1, line2) != 0) { // not parallel
//         return Point();
//     }
//     else { // parallel
//         if (lcross(Line(line1.first, line2.second), Line(line1.second, line2.first))  != 0) { // not the same
//                 int a1 = line1.first.y - line1.second.y;
//                 int b1 = line1.first.x - line1.second.x;
//                 int c1 = line1.first.x * line1.second.y - line1.second.x * line1.first.y;
//                 int a2 = line2.first.y - line2.second.y;
//                 int b2 = line2.first.x - line2.second.x;
//                 int c2 = line2.first.x * line2.second.y - line2.second.x * line2.first.y;
//                 int det = a1 * b2 - a2 * b1;
//                 int x = (b1 * c2 - b2 * c1) / det;
//                 int y = (a2 * c1 - a1 * c2) / det;
//                 return Point(x, y);
//         }
//         else { // the same
//             return Point(); // !!!!!!!!!!!!!!!!!!!!!!!!!!!!
//         }
//     }
// }

// Point perc(Line srp, Vordiag vordiag, Point& smezh_point)
// {
//     int n = vordiag.vorlines.size();
//     Point ret;
//     Point check = Point();
//     for (int i = 0; i < n; i++) {
//         ret = percline(srp, vordiag.vorlines[i].line);
//         if (ret != check)
//             break;
//     }
//     return ret;
// }



// Vordiag merge(Vordiag l_vect, Vordiag r_vect)
// {
//     Point per, perl, perr, check = Point();
//     Line srp, otr;
//     otr = upper_bound(l_vect, r_vect);
//     Point smezh_point = check;
//     while(1) {
//         srp = serp(otr);
//         perl = perc(srp, l_vect, smezh_point);
//         perr =  perc(srp, r_vect, smezh_point);
//         if (perl == check && perr == check)
//             break;
//         if (perl.y < perr.y) {
//             per = perl;
//             //otr.first = smezh_point.get_cord(); !!!!!!!!!!!!!!!!!!!!!
//         }
//         else {
//             per = perr;
//             //otr.second = smezh_point.get_cord(); !!!!!!!!!!!!!!!!!!!!!
//         }
//     }
//     Vordiag m_vect = l_vect; // !!!!!!!!!!!!!!!!!!!!!
//     return m_vect;
// }


// Vordiag iter(Vordiag vect)
// {
//     Vordiag l_vect, r_vect;
//     divide(vect, l_vect, r_vect);
//     if (l_vect.vorlines.size() > 1)
//         iter(l_vect);
//     if (r_vect.vorlines.size() > 1)
//         iter(r_vect);
//     Vordiag m_vect = merge(l_vect, r_vect);
//     return m_vect;
// }



std::vector<float> getrgb(int color) {
    std::vector<float> rgbcolor(3, 0);
    float step = 3/(static_cast<float>(NUMBER_OF_POINTS));
    while (color > 0) {
        rgbcolor[color%3] += step;
        color/=3;
    }
    return rgbcolor;
}


// std::vector<float> getrgb(int color) { 
//     std::vector<float> rgbcolor(3, 0);
//     float step = 3/(static_cast<float>(NUMBER_OF_POINTS + 3 - NUMBER_OF_POINTS % 3));
//     while (1) {
//         rgbcolor[color%3] += step;
//         color/=3;
//         if (color <= 0)
//             break;
//     }
//     return rgbcolor;
// }

// std::vector<float> getrgb(int color) { 
//     std::vector<float> rgbcolor(3, 0);
//     std::cout << color << " ";
//     int t =color;
//     float step = 3/(static_cast<float>(NUMBER_OF_POINTS + 3 - NUMBER_OF_POINTS % 3));
//     while (1) {
//         rgbcolor[color%3] += step;
//         color/=3;
//         if (color <= 0)
//             break;
//     }
//     if (t == -1) {
//        // std::cout << "??";
//        rgbcolor[0] = 0;
//        // std::cout << rgbcolor[0] << std::endl;
//     }
//     for (auto i:rgbcolor) {
//         std::cout << i << " ";
//     }
//     std::cout << std::endl;
//     return rgbcolor;
// }
int recalc(std::vector<std::vector<Pixel>>& pixels, std::vector<Point>& points)
{
    unsigned int start = clock(), end = 0;
    int ret = 0, t = 0;
    std::vector<int> sx(points.size());
    std::vector<int> sy(points.size());
    std::vector<int> ns(points.size());
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (pixels[i][j].color != -1) {
                sx[pixels[i][j].color] += pixels[i][j].x;
                sy[pixels[i][j].color] += pixels[i][j].y;
                ns[pixels[i][j].color]++;
            }
        }
    }
    for (int i = 0; i < points.size(); i++) {
        t = sx[i] / ns[i];
        if (points[i].x == t)
            ret+=1;
        else
            points[i].x = t;
        t = sy[i] / ns[i];
        if (points[i].y == t)
            ret+=1;
        else
            points[i].y = t;
    }
    end = clock();
    std::cout << "recalc " << end-start << std::endl;
    std::cout << ret << std::endl;
    return ret;
}
int calculate(std::vector<std::vector<Pixel>>& pixels, std::vector<Point>& points)
{
    unsigned int start = clock(), end = 0;
    //std::cout << "start\n";
    int d = 0, maxd = 1000000;
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            maxd = 1000000;
            pixels[i][j].x = j, pixels[i][j].y = i;
            for (int k = 0; k < NUMBER_OF_POINTS; k++) {
                d = dist(pixels[i][j], points[k]);
                if (d < maxd) {
                    maxd = d;
                    pixels[i][j].color = k;
                    if (maxd == 0) {
                        pixels[i][j].color = COLOR_OF_POINT;
                        break;
                    }
                }
            }
        }
    }
        end = clock();
  std::cout << "main " << end-start << std::endl;
    //std::cout << "end\n";
    // std::cout << "Hi\n";



    // std::vector<std::pair<Pixel, std::set<int>>> ref;
    // std::set<int> st;
    // for (int i = 1; i < 6; i++) {
    //     for (int j = 1; j < WIDTH-1; j++) {
    //         st.clear();
    //         for (int k = -1; k <= 1; k++) {
    //             for (int l = -1; l <= 1; l++) {
    //                 if (pixels[i+k][j+l].color != 9)
    //                     st.insert(pixels[i+k][j+l].color);
    //                 if (i+k == HEIGHT)
    //                     st.insert(-1);
    //                 if (i+k ==0)
    //                     st.insert(-2);
    //                 if (j+l == WIDTH)
    //                     st.insert(-3);
    //                 if (j+l == 0)
    //                     st.insert(-4);
    //             }
    //         }
    //         if (st.size() >= 3)
    //             ref.push_back(std::make_pair(pixels[i][j], st));
    //     }
    // }

    // std::cout<< ref.size() << std::endl;
    // for (int i = 0; i < ref.size(); i++) {
    //     std::cout << i << " " << ref[i].first.x << " " << ref[i].first.y << " ";
    //     for (auto j:ref[i].second) {
    //         std::cout << j << " ";
    //     }
    //     std::cout << "\n";
    // }
    // std::cout << "Hi\n";

    // for (int i = 0; i < points.size(); i++) {
    //     for (int j = 0; j < ref.size(); j++) {
    //         if (ref[j].second.find(i) != ref[j].second.end() || *ref[j].second.end() == i) {
    //             points[i].refpixels.push_back(ref[j].first);
    //         }
    //     }
    // }
    // std::cout << "Hi\n";

    // for (int i = 0; i < points.size(); i++) {
    //     int sx = 0, sy = 0;
    //     for (int j = 0; j < points[i].refpixels.size(); j++) {
    //         std::cout << j << std::endl;

    //         sx += points[i].refpixels[j].x;
    //         sy += points[i].refpixels[j].y;

    //     }
    //     points[i].x = sx / points[i].refpixels.size();
    //     points[i].y = sy / points[i].refpixels.size();
    // }



    //std::cout << std::endl << std::endl;

    // for (int i = HEIGHT - 1; i >= 0; i--) {
    //     for (int j = 0; j < WIDTH; j++) {
    //         std::cout << pixels[i][j].color << " ";
    //     }
    //     std::cout << std::endl;
    // }
    return 0;
}