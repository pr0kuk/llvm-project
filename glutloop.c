#include "libs.h"

#ifdef _WIN32
    #include <C:/Users/alex-/gcc/include/GL/freeglut.h>
#else
    #include <GL/freeglut.h>
#endif

void display();
void timf(int value);

void loop() {
    glutDisplayFunc(display);
    glutTimerFunc(FRAME_TIME, timf, 0); // Set up timer for 40ms, about 25 fps
    glutMainLoop();
}

void exit_loop() {
    glutLeaveMainLoop();
}

void set_timer(int value) {
    glutTimerFunc(FRAME_TIME, timf, 0); // Set up timer for 40ms, about 25 fps
}