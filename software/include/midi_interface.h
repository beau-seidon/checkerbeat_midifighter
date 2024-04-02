#pragma once

#include <Arduino.h>
#include <MIDI.h>

#include "button_monitor.h"
#include "pot_monitor.h"
#include "joystick_monitor.h"



#define MIDI_CHANNEL 10
#define DEFAULT_VELOCITY 100


const int POT_CC[3] = { 20, 21, 22 };
const int JS_CC[2] = { 24, 25 };

const int DEBOUNCE_TIME = 20;


void midi_setup(void);
// void pots_to_midi(void);
// bool js_changed(float js, float prev_js);
// void joystick_to_midi(void);
bool debounce(int i);
void buttons_to_midi(byte shiftreg1, byte shiftreg2);
void midi_handler(void);
void activity_led_off(void);
