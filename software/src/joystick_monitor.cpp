#include "joystick_monitor.h"



// float joystick_x = 0.0;
int joystick_x = 0;
int joystick_y = 0;

// float prev_joystick_x = -1.0;
int prev_joystick_x = -1;
int prev_joystick_y = -1;

float js_x_cal_ofst = 153;

// twice the min value required
float js_x_deadzone = 0;
float js_y_deadzone = 0;

// float range_limit(float min, float val, float max) {
//     if(val > max) return max;
//     if(val < min) return min;
//     return val;
// }


void joystick_setup() {
    pinMode(JOYSTICK_PINS[0], INPUT);  // X-Axis (mod wheel)
    pinMode(JOYSTICK_PINS[1], INPUT);  // Y-Axis (pitch wheel)
}


void joystick_handler() {
    // joystick_x = range_limit(-1.0, (2.0 * ((analogRead(JOYSTICK_PINS[0]) + js_x_cal_ofst) / 4095.0) - 1.0), 1.0);
    joystick_x = 127 * (analogRead(JOYSTICK_PINS[0]) / 4095.0);
    joystick_y = 127 * (analogRead(JOYSTICK_PINS[1]) / 4095.0);
}
