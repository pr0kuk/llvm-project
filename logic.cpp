#include "libs.hpp"
#include "point.hpp"
static int flag_no_recalc = 0;
static std::vector<CenterPoint> points(NUMBER_OF_POINTS);
static std::vector<std::vector<Point>> pixels(HEIGHT, std::vector<Point>(WIDTH));
//static float const step = 3/(static_cast<float>(NUMBER_OF_POINTS));
int  gl_init(int argc, char** argv);
void gl_start();
void gl_put_pixel(Point& j, std::vector<float> rgbcolor);
void gl_flush();
void set_timer(int value);
int  loop();

void print_time(char* const str, unsigned int start) {
    std::cout << str << " " << clock() - start << std::endl;
}

int dist(Point& a, CenterPoint& b) {
    return (b.x-a.x)*(b.x-a.x)+(b.y-a.y)*(b.y-a.y);
}

std::vector<float> getrgb(int color) {
    constexpr float step = 3/(static_cast<float>(NUMBER_OF_POINTS));
    std::vector<float> rgbcolor(3, 0);
    for (; color > 0; color /= 3)
        rgbcolor[color%3] += step;
    return rgbcolor;
}

int calc_new_centers(std::vector<std::vector<Point>>& pixels, std::vector<CenterPoint>& points) {
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

int calc_vor_diag(std::vector<std::vector<Point>>& pixels, std::vector<CenterPoint>& points) {
    unsigned int start = clock();
    for (int i = 0; i < HEIGHT; i++)
        for (int j = 0, maxd = MAX_INT; j < WIDTH; j++, maxd = MAX_INT, pixels[i][j].x = j, pixels[i][j].y = i)
            for (int k = 0, d = 0; k < NUMBER_OF_POINTS && maxd > 0; k++)
                if ((d = dist(pixels[i][j], points[k])) < maxd)
                    maxd = d, pixels[i][j].color = k;
    print_time("vordiag", start);
    return 0;
}

void display() {
    calc_vor_diag(pixels, points);
    unsigned int start = clock();
    gl_start();
    for (auto i : pixels)
        for (auto j : i)
            gl_put_pixel(j, getrgb(j.color));
    gl_flush();
    print_time("graphic", start);
}

void timf(int value) {
    if (flag_no_recalc == 0) {
        int ret = calc_new_centers(pixels, points);
        if (ret < NUMBER_OF_POINTS * 2)
            display();
        else {
            std::cout << "END" << std::endl;
            flag_no_recalc = 1;
        }
    }
    set_timer(value);
}


int main(int argc, char** argv) {
    for (auto i = points.begin(); i < points.end(); i++)
            i->x = rand() % WIDTH, i->y = rand() % HEIGHT;
    gl_init(argc, argv);
    loop();
    return 0;
}