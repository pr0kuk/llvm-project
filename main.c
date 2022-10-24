#include "libs.h"

static int show_window = 1;
static int flag_no_recalc = 0;
static struct Point points[NUMBER_OF_POINTS];
static struct Point pixels[HEIGHT][WIDTH];

int dist(struct Point* a, struct Point* b) {
    return (b->x-a->x)*(b->x-a->x)+(b->y-a->y)*(b->y-a->y);
}

int calc_new_centers() {
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

void calc_vor_diag() {
    for (int i = 0; i < HEIGHT; i++)
        for (int j = 0, maxd = MAX_INT; j < WIDTH; pixels[i][j].x = j, pixels[i][j].y = i, j++, maxd = MAX_INT)
            for (int k = 0, d = 0; k < NUMBER_OF_POINTS && maxd > 0; k++)
                if ((d = dist(&pixels[i][j], &points[k])) < maxd)
                    maxd = d, pixels[i][j].color = k;
}

void display() {
    calc_vor_diag();
    gl_start();
    for (int i = 0; i < HEIGHT; i++)
        for (int j = 0; j < WIDTH; j++)
            gl_put_pixel(&pixels[i][j]);
    gl_flush();
}

void timf(int value) {
    if (flag_no_recalc == 0 /*&& pause_window == 0*/) {
        if (calc_new_centers() < NUMBER_OF_POINTS * 2)
            display();
        else 
            flag_no_recalc = 1;
    }
    set_timer(value);
}

void reset_picture() {
    for (int i = 0; i < NUMBER_OF_POINTS; i++)
        points[i].x = int_rand() % WIDTH, points[i].y = int_rand() % HEIGHT;
    calc_vor_diag();
    flag_no_recalc = 0;
}

int main(int argc, char** argv) {
    gl_init(argc, argv);
    reset_picture();
    loop();
    return 0;
}