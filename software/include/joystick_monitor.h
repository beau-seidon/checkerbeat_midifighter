#pragma once

#include <Arduino.h>



const int JOYSTICK_PINS[2] = { 35, 34 };


float range_limit(float, float, float);
void joystick_setup();
void joystick_handler();
