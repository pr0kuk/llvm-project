#include "libs.hpp"
//#include <C:/Users/alex-/gcc/include/GL/freeglut.h>
//#include <GL/gl.h>
#include <GL/freeglut.h>
#include "point.hpp"
#include "line.hpp"
#include "vordiag.hpp"
#include "vorline.hpp"
#include "pixel.hpp"
int calculate(std::vector<std::vector<Pixel>>& pixels, std::vector<Point>& points);
int recalc(std::vector<std::vector<Pixel>>& pixels, std::vector<Point>& points);
std::vector<float> getrgb(int color);

static int flag_no_recalc = 0;
static std::vector<Point> points(NUMBER_OF_POINTS);
static std::vector<std::vector<Pixel>> pixels(HEIGHT, std::vector<Pixel>(WIDTH));
    
void timf(int value) {
    if (flag_no_recalc == 0) {
        int ret = recalc(pixels, points);
        if (ret < NUMBER_OF_POINTS * 2)
            glutPostRedisplay();
        else
            flag_no_recalc = 1;
    }
    std::cout << "flag " << flag_no_recalc << std::endl;
    glutTimerFunc(FRAME_TIME, timf, 0); // Setup next timer
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    calculate(pixels, points);
    unsigned int start = clock(), end = 0;

    glBegin(GL_POINTS);
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            std::vector<float> rgbcolor = getrgb(pixels[i][j].color);
            glColor3f(rgbcolor[0], rgbcolor[1], rgbcolor[2]);
            glVertex2f((static_cast<float>(pixels[i][j].x)/WIDTH - 0.5)*2, (static_cast<float>(pixels[i][j].y)/HEIGHT - 0.5) * 2);
        }
    }
    glEnd();

    glFlush();
    end = clock();
    std::cout << "graphic " << end-start << std::endl;
}

int main(int argc, char** argv) {
    for (int i = 0; i < NUMBER_OF_POINTS; i++)
        points[i].x = rand() % WIDTH, points[i].y = rand() % HEIGHT;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(1000, 90);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Lloyd");
    glutDisplayFunc(display);
    glutTimerFunc(FRAME_TIME, timf, 0); // Set up timer for 40ms, about 25 fps
    glutMainLoop();
}