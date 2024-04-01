#pragma once

#include <Arduino.h>



const int POT_PINS[3] = {33, 32, 25};


void pot_setup();
void pot_handler();
