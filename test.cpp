#include "libs.hpp"
#include <C:/Users/alex-/gcc/include/GL/freeglut.h>
#include "point.hpp"
#include "line.hpp"
#include "vordiag.hpp"
#include "vorline.hpp"
#include "pixel.hpp"
#include "rgbcolor.hpp"
int calculate(std::vector<std::vector<Pixel>>& pixels, std::vector<Point>& points);
std::vector<float> getrgb(int color);
std::vector<Point> points(NUMBER_OF_POINTS);
// Clears the current window and draws a triangle.
void display() {

  // Set every pixel in the frame buffer to the current clear color.
  glClear(GL_COLOR_BUFFER_BIT);
   std::vector<std::vector<Pixel>> pixels(HEIGHT, std::vector<Pixel>(WIDTH));
   std::vector<std::pair<Pixel, std::set<int>>> ref;
   calculate(pixels, points);

  //float Coord[] = {-0.8f, -0.8f,0, 0};

//glEnableClientState(GL_VERTEX_ARRAY);
//glVertexPointer(2, GL_FLOAT, 0, Coord);
  // Drawing is done by specifying a sequence of vertices.  The way these
  // vertices are connected (or not connected) depends on the argument to
  // glBegin.  GL_POLYGON constructs a filled polygon.
  /*glBegin(GL_POLYGON);
  
    glColor3f(1, 0, 0); glVertex3f(-0.6, -0.75, 0.5);
    glColor3f(0, 1, 0); glVertex3f(0.6, -0.75, 0);
    glColor3f(0, 0, 1); glVertex3f(0, 0.75, 0);
  glEnd();*/

  glBegin(GL_POINTS);
	//for (int Point = 0; Point < 4/ 2; Point++) 
		//glArrayElement(Point);
		for (int i = 0; i < HEIGHT; i++) {
			for (int j = 0; j < WIDTH; j++) {
				std::vector<float> rgbcolor = getrgb(pixels[i][j].color);
				//std::cout << pixels[i][j].color << " " << rgbcolor[0] << " " << rgbcolor[1] << " " << rgbcolor[2] << std::endl;
				//std::cout << i << " " << j << " " << pixels[i][j].x << " " << pixels[i][j].y << " "  << static_cast<float>(pixels[i][j].x)/WIDTH - 0.5 << " " <<static_cast<float>(pixels[i][j].y)/HEIGHT - 0.5 << std::endl;
				glColor3f(rgbcolor[0], rgbcolor[1], rgbcolor[2]); glVertex2f((static_cast<float>(pixels[i][j].x)/WIDTH - 0.5)*2, (static_cast<float>(pixels[i][j].y)/HEIGHT - 0.5) * 2);
			}
		}
		
  glEnd();

  // Flush drawing command buffer to make drawing happen as soon as possible.
  glFlush();
  //system("pause");
}

// Initializes GLUT, the display mode, and main window; registers callbacks;
// enters the main event loop.
int main(int argc, char** argv) {


    for (int i = 0; i < NUMBER_OF_POINTS; i++)
    {
        points[i].x = rand()%WIDTH;//i*WIDTH/NUMBER_OF_POINTS;
        points[i].y = rand()%HEIGHT;//i*HEIGHT/NUMBER_OF_POINTS;
    }
  // Use a single buffered window in RGB mode (as opposed to a double-buffered
  // window or color-index mode).
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

  // Position window at (80,80)-(480,380) and give it a title.
  glutInitWindowPosition(1000, 90);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutCreateWindow("A Simple Triangle");

  // Tell GLUT that whenever the main window needs to be repainted that it
  // should call the function display().
  glutDisplayFunc(display);

  // Tell GLUT to start reading and processing events.  This function
  // never returns; the program only exits when the user closes the main
  // window or kills the process.
  glutMainLoop();
}