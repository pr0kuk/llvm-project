#include "libs.hpp"
#include <C:/Users/alex-/gcc/include/GL/freeglut.h>
//#include <GL/freeglut.h>
#include "point.hpp"
void getrgb(int color, float* rgbcolor);
void releaseKey(unsigned char key, int x, int y);
void reset_picture();
void gl_start() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
}

void gl_put_pixel(Point* j) {
    float rgbcolor[3] = {0, 0, 0};
    getrgb(j->color, rgbcolor);
    glColor3f(rgbcolor[0], rgbcolor[1], rgbcolor[2]);
    glVertex2f((static_cast<float>(j->x)/WIDTH - 0.5)*2, (static_cast<float>(j->y)/HEIGHT - 0.5) * 2);
}

void gl_flush() {
    glEnd();
    glFlush();
}

int  gl_init(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(1000, 90);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Lloyd");
    glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(releaseKey);
    return 0;
}