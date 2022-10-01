#include "libs.hpp"
#include <C:/Users/alex-/gcc/include/GL/freeglut.h>
//#include <GL/freeglut.h>
#include "point.hpp"
int calc_new_centers(std::vector<std::vector<Point>>& pixels, std::vector<CenterPoint>& points);
int calc_vor_diag(std::vector<std::vector<Point>>& pixels, std::vector<CenterPoint>& points);
std::vector<float> getrgb(int color);

static int flag_no_recalc = 0;
static std::vector<CenterPoint> points(NUMBER_OF_POINTS);
static std::vector<std::vector<Point>> pixels(HEIGHT, std::vector<Point>(WIDTH));
    
void timf(int value) {
    if (flag_no_recalc == 0) {
        int ret = calc_new_centers(pixels, points);
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
    calc_vor_diag(pixels, points);
    unsigned int start = clock(), end = 0;

    glBegin(GL_POINTS);
    for (auto i : pixels) {
        for (auto j : i) {
            std::vector<float> rgbcolor = getrgb(j.color);
            glColor3f(rgbcolor[0], rgbcolor[1], rgbcolor[2]);
            glVertex2f((static_cast<float>(j.x)/WIDTH - 0.5)*2, (static_cast<float>(j.y)/HEIGHT - 0.5) * 2);
        }
    }
    glEnd();

    glFlush();
    end = clock();
    std::cout << "graphic " << end-start << std::endl;
}

int main(int argc, char** argv) {
    for (auto i = points.begin(); i < points.end(); i++)
            i->x = rand() % WIDTH, i->y = rand() % HEIGHT;
    for (auto i : points)
        std::cout << i.x << std::endl;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(1000, 90);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Lloyd");
    glutDisplayFunc(display);
    glutTimerFunc(FRAME_TIME, timf, 0); // Set up timer for 40ms, about 25 fps
    glutMainLoop();
}