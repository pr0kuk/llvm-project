#include "libs.h"
static int show_window = 1;
void display();
void timf(int value);

void loop() {
    display();
    while (show_window == 1)
        timf(FRAME_TIME);
}

void exit_loop() {
    show_window = 0;
}

void set_timer(int value) {}