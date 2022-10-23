#include "libs.h"
static int pause_window = 0;

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