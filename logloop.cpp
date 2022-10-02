#include "libs.hpp"

void display();
void timf(int value);

int loop() {
    display();
    while (1)
        timf(FRAME_TIME);
    return 0;
}

void set_timer(int value) {}