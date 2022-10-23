#include "libs.h"
#ifdef _WIN32
    #include <C:/Users/alex-/gcc/include/GL/freeglut.h>
#else
    #include <GL/freeglut.h>
#endif
#include <stdlib.h>

static float const step = 3/((float)(NUMBER_OF_POINTS));

void gl_start() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
}

void getrgb(int color, float* rgbcolor) {
    for (; color > 0; color /= 3)
        rgbcolor[color%3] += step;
}

void gl_put_pixel(struct Point* j) {
    float rgbcolor[3] = {0, 0, 0};
    getrgb(j->color, rgbcolor);
    glColor3f(rgbcolor[0], rgbcolor[1], rgbcolor[2]);
    glVertex2f(((float)(j->x)/WIDTH - 0.5)*2, ((float)(j->y)/HEIGHT - 0.5) * 2);
}

void gl_flush() {
    glEnd();
    glFlush();
}

void gl_init(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(1000, 90);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Lloyd");
    glutIgnoreKeyRepeat(1);
    //lutKeyboardFunc(releaseKey);
}

int int_rand() {
    return rand();
}