#include "libs.hpp"
#include "point.hpp"
#include <stdlib.h>
#define KEY_ESC 27
#define KEY_SPACE 32
#define KEY_R 'r'
static int show_window = 1;
static int pause_window = 0;
static int flag_no_recalc = 0;
static Point points[NUMBER_OF_POINTS];
static Point pixels[HEIGHT][WIDTH];
static float const step = 3/(static_cast<float>(NUMBER_OF_POINTS));
int  gl_init(int argc, char** argv);
void gl_start();
void gl_put_pixel(Point* j);
void gl_flush();
void set_timer(int value);
int  loop();
void exit_loop();

int dist(Point* a, Point* b) {
    return (b->x-a->x)*(b->x-a->x)+(b->y-a->y)*(b->y-a->y);
}

void getrgb(int color, float* rgbcolor) {
    for (; color > 0; color /= 3)
        rgbcolor[color%3] += step;
}

int calc_new_centers(Point pixels[HEIGHT][WIDTH], Point* points) {
    int ret = 0, t = 0;
    int sx[NUMBER_OF_POINTS], sy[NUMBER_OF_POINTS], ns[NUMBER_OF_POINTS]; 
    for (int i = 0; i < NUMBER_OF_POINTS; i++)
        sx[i] = 0, sy[i] = 0, ns[i] = 0;
    for (int i = 0; i < HEIGHT; i++)
        for (int j = 0; j < WIDTH; j++)
            if (pixels[i][j].color >= 0)
                sx[pixels[i][j].color] += pixels[i][j].x, sy[pixels[i][j].color] += pixels[i][j].y, ns[pixels[i][j].color]++;
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

int calc_vor_diag(Point pixels[HEIGHT][WIDTH], Point* points) {
    for (int i = 0; i < HEIGHT; i++)
        for (int j = 0, maxd = MAX_INT; j < WIDTH; pixels[i][j].x = j, pixels[i][j].y = i, j++, maxd = MAX_INT)
            for (int k = 0, d = 0; k < NUMBER_OF_POINTS && maxd > 0; k++)
                if ((d = dist(&pixels[i][j], &points[k])) < maxd)
                    maxd = d, pixels[i][j].color = k;
    return 0;
}

void display() {
    calc_vor_diag(pixels, points);
    gl_start();
    for (int i = 0; i < HEIGHT; i++)
        for (int j = 0; j < WIDTH; j++)
            gl_put_pixel(&pixels[i][j]);
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
    for (int i = 0; i < NUMBER_OF_POINTS; i++)
        points[i].x = rand() % WIDTH, points[i].y = rand() % HEIGHT;
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