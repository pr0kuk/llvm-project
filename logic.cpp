#include "libs.hpp"
#include "point.hpp"
static float const step = 3/(static_cast<float>(NUMBER_OF_POINTS));

int dist(Point& a, CenterPoint& b)
{
    return (b.x-a.x)*(b.x-a.x)+(b.y-a.y)*(b.y-a.y);
}

std::vector<float> getrgb(int color) {
    std::vector<float> rgbcolor(3, 0);
    for (; color > 0; color /= 3)
        rgbcolor[color%3] += step;
    return rgbcolor;
}

int calc_new_centers(std::vector<std::vector<Point>>& pixels, std::vector<CenterPoint>& points)
{
    unsigned int start = clock(), end = 0;
    int ret = 0, t = 0, sz = NUMBER_OF_POINTS;
    std::vector<int> sx(sz), sy(sz), ns(sz);
    for (int i = 0; i < HEIGHT; i++)
        for (int j = 0; j < WIDTH; j++)
            if (pixels[i][j].color >= 0)
                sx[pixels[i][j].color] += pixels[i][j].x, sy[pixels[i][j].color] += pixels[i][j].y, ns[pixels[i][j].color]++;
    for (int i = 0; i < points.size(); i++) {
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
    end = clock();
    std::cout << "recalc " << end-start << std::endl;
    return ret;
}

int calc_vor_diag(std::vector<std::vector<Point>>& pixels, std::vector<CenterPoint>& points)
{
    unsigned int start = clock(), end = 0;
    for (int i = 0, d = 0; i < HEIGHT; i++) {
        for (int j = 0, maxd = MAX_INT; j < WIDTH; j++, maxd = MAX_INT) {
            pixels[i][j].x = j, pixels[i][j].y = i;
            for (int k = 0, d = dist(pixels[i][j], points[0]); k < NUMBER_OF_POINTS && maxd > 0; k++, d = dist(pixels[i][j], points[k]))
                if (d < maxd)
                    maxd = d, pixels[i][j].color = k;
        }
    }
    end = clock();
    std::cout << "main " << end-start << std::endl;
    return 0;
}