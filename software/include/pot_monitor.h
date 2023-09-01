#pragma once
#include <Arduino.h>


///////////////////////////////////////////////////////////////////////////////
static const int POT_PINS[3] = {33, 32, 25};

static int pots[3] = {0};
static int prev_pots[3] = {-1};

static unsigned long Tp[3] = {millis()};


///////////////////////////////////////////////////////////////////////////////
void pot_setup();
void pot_handler();


///////////////////////////////////////////////////////////////////////////////
void pot_setup() {
	pinMode(POT_PINS[0], INPUT);  // Velocity
	pinMode(POT_PINS[1], INPUT);  // CC#20
	pinMode(POT_PINS[2], INPUT);  // CC#21
}


void pot_handler() {
    for(int i = 0; i < 3; i++) {
        pots[i] = 127 * (analogRead(POT_PINS[i]) / 4095.0);
    }
}
