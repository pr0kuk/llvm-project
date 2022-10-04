#pragma once
#define HEIGHT 800
#define WIDTH 800
#define NUMBER_OF_POINTS 10
#define FRAME_TIME 10
#define COLOR_OF_POINT -1

#define MAX_INT 10e8
#define KEY_ESC 27
#define KEY_SPACE 32
#define KEY_R 'r'

#include "point.h"

void gl_init(int argc, char** argv);
void gl_start();
void gl_put_pixel(struct Point* j);
void gl_flush();
void set_timer(int value);
void loop();
void exit_loop();
void releaseKey(unsigned char key, int x, int y);
void reset_picture();
int  int_rand();