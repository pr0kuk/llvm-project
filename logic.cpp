#include "libs.hpp"
#include "point.hpp"
#define KEY_ESC 27
#define KEY_SPACE 32
#define KEY_R 'r'
static int show_window = 1;
static int pause_window = 0;
static int flag_no_recalc = 0;
static std::vector<Point> points(NUMBER_OF_POINTS);
static std::vector<std::vector<Point>> pixels(HEIGHT, std::vector<Point>(WIDTH));
int  gl_init(int argc, char** argv);
void gl_start();
void gl_put_pixel(Point& j, std::vector<float> rgbcolor);
void gl_flush();
void set_timer(int value);
int  loop();
void exit_loop();

int dist(Point& a, Point& b) {
    return (b.x-a.x)*(b.x-a.x)+(b.y-a.y)*(b.y-a.y);
}

std::vector<float> getrgb(int color) {
    constexpr float step = 3/(static_cast<float>(NUMBER_OF_POINTS));
    std::vector<float> rgbcolor(3, 0);
    for (; color > 0; color /= 3)
        rgbcolor[color%3] += step;
    return rgbcolor;
}

int calc_new_centers(std::vector<std::vector<Point>>& pixels, std::vector<Point>& points) {
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
    return ret;
}

int calc_vor_diag(std::vector<std::vector<Point>>& pixels, std::vector<Point>& points) {
    for (int i = 0; i < HEIGHT; i++)
        for (int j = 0, maxd = MAX_INT; j < WIDTH; maxd = MAX_INT, pixels[i][j].x = j, pixels[i][j].y = i, j++)
            for (int k = 0, d = 0; k < NUMBER_OF_POINTS && maxd > 0; k++)
                if ((d = dist(pixels[i][j], points[k])) < maxd)
                    maxd = d, pixels[i][j].color = k;
    return 0;
}

void display() {
    calc_vor_diag(pixels, points);
    gl_start();
    for (auto i : pixels)
        for (auto j : i)
            gl_put_pixel(j, getrgb(j.color));
    gl_flush();
}

void timf(int value) {
    if (flag_no_recalc == 0 && pause_window == 0) {
        if (calc_new_centers(pixels, points) < NUMBER_OF_POINTS * 2)
            display();
        else
            flag_no_recalc = 1;
    }
    set_timer(value);
}

void reset_picture() {
    for (auto i = points.begin(); i < points.end(); i++)
            i->x = rand() % WIDTH, i->y = rand() % HEIGHT;
    calc_vor_diag(pixels, points);
    flag_no_recalc = 0;
}

void releaseKey(unsigned char key, int x, int y) {
    switch(key) {
        case KEY_ESC:
            exit_loop(); break;
        case KEY_SPACE:
            pause_window ^= 1; break;
        case KEY_R:
            reset_picture(); break;
    }
}

int main(int argc, char** argv) {
    gl_init(argc, argv);
    reset_picture();
    loop();
    return 0;
}