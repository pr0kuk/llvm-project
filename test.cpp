#include "libs.hpp"
#include <C:/Users/alex-/gcc/include/GL/freeglut.h>
#include "point.hpp"
#include "line.hpp"
#include "vordiag.hpp"
#include "vorline.hpp"
#include "pixel.hpp"
int flag_no_recalc = 0;
int calculate(std::vector<std::vector<Pixel>>& pixels, std::vector<Point>& points);
int recalc(std::vector<std::vector<Pixel>>& pixels, std::vector<Point>& points);
std::vector<float> getrgb(int color);
std::vector<Point> points(NUMBER_OF_POINTS);
std::vector<std::vector<Pixel>> pixels(HEIGHT, std::vector<Pixel>(WIDTH));


void timf(int value) {
  if (flag_no_recalc == 0) {
    std::cout <<"CALL\n";
    int ret = recalc(pixels, points);
    std::cout << "ret is " << ret << std::endl;
    if (ret < NUMBER_OF_POINTS * 2) {
      std::cout<<"there\n";
      glutPostRedisplay();
    }
    else
      flag_no_recalc = 1;
  }
  std::cout << "flag " << flag_no_recalc << std::endl;
  glutTimerFunc(40, timf, 0); // Setup next timer
}
void display() {
        std::cout << "CHECK4\n";
  
  glClear(GL_COLOR_BUFFER_BIT);
  //std::vector<std::pair<Pixel, std::set<int>>> ref;
  calculate(pixels, points);
  unsigned int start = clock(), end = 0;
  glBegin(GL_POINTS);
        std::cout << "CHECK\n";
  
		for (int i = 0; i < HEIGHT; i++) {
			for (int j = 0; j < WIDTH; j++) {
        // std::cout << "!" << pixels[i][j].color << std::endl;
				 std::vector<float> rgbcolor = getrgb(pixels[i][j].color);
        // std::cout << i << " " << j << " ";
        //     for (auto k:rgbcolor) {
        // std::cout << k << " ";
    //}
    // std::cout << (static_cast<float>(pixels[i][j].x)/WIDTH - 0.5)*2 << " " << (static_cast<float>(pixels[i][j].y)/HEIGHT - 0.5) * 2 << std::endl;
    // std::cout << std::endl;
				glColor3f(rgbcolor[0], rgbcolor[1], rgbcolor[2]);
        // std::cout << "CHECK\n";
        glVertex2f((static_cast<float>(pixels[i][j].x)/WIDTH - 0.5)*2, (static_cast<float>(pixels[i][j].y)/HEIGHT - 0.5) * 2);
        // std::cout << "CHECK2\n";
			}
		}
        std::cout << "CHECK3\n";

  glEnd();
  glFlush();
    end = clock();
  std::cout << "graphic " << end-start << std::endl;
}

int main(int argc, char** argv) {
  for (int i = 0; i < NUMBER_OF_POINTS; i++)
  {
    points[i].x = rand() % WIDTH;
    points[i].y = rand() % HEIGHT;
  }
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(1000, 90);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutCreateWindow("Lloyd");
  glutDisplayFunc(display);
  glutTimerFunc(40, timf, 0); // Set up timer for 40ms, about 25 fps
  glutMainLoop();
}