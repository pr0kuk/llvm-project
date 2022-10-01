#include "libs.hpp"
#include "point.hpp"
//static float const step = 3/(static_cast<float>(NUMBER_OF_POINTS));

void print_time(char* const str, unsigned int start) {
    std::cout << str << " " << clock() - start << std::endl;
}

int dist(Point& a, CenterPoint& b)
{
    return (b.x-a.x)*(b.x-a.x)+(b.y-a.y)*(b.y-a.y);
}

std::vector<float> getrgb(int color) {
    constexpr float step = 3/(static_cast<float>(NUMBER_OF_POINTS));
    std::vector<float> rgbcolor(3, 0);
    for (; color > 0; color /= 3)
        rgbcolor[color%3] += step;
    return rgbcolor;
}

int calc_new_centers(std::vector<std::vector<Point>>& pixels, std::vector<CenterPoint>& points)
{
    unsigned int start = clock();
    int ret = 0, t = 0, sz = NUMBER_OF_POINTS;
    std::vector<int> sx(sz), sy(sz), ns(sz);
    for (auto i : pixels)
        for (auto j : i)
            if (j.color >= 0)
                sx[j.color] += j.x, sy[j.color] += j.y, ns[j.color]++;
    for (int i = 0; i < NUMBER_OF_POINTS; i++) {
        t = sx[i] / ns[i];
        if (points[i].x == t)
            ret += 1;
        else
            points[i].x = t;
        t = sy[i] / ns[i];
        if (points[i].y == t)
            ret += 1;
        else
            points[i].y = t;
    }
    print_time("new_centers", start);
    return ret;
}

int calc_vor_diag(std::vector<std::vector<Point>>& pixels, std::vector<CenterPoint>& points)
{
    unsigned int start = clock();
    for (int i = 0; i < HEIGHT; i++)
        for (int j = 0, maxd = MAX_INT; j < WIDTH; j++, maxd = MAX_INT, pixels[i][j].x = j, pixels[i][j].y = i)
            for (int k = 0, d = 0; k < NUMBER_OF_POINTS && maxd > 0; k++)
                if ((d = dist(pixels[i][j], points[k])) < maxd)
                    maxd = d, pixels[i][j].color = k;
    print_time("vordiag", start);
    return 0;
}