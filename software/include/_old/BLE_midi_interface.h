#pragma once
#include <Arduino.h>

#include <BLEMIDI_Transport.h>
#include <hardware/BLEMIDI_ESP32_NimBLE.h>
// #include <hardware/BLEMIDI_ESP32.h>
// #include <hardware/BLEMIDI_nRF52.h>
// #include <hardware/BLEMIDI_ArduinoBLE.h>

#include "button_monitor.h"
#include "pot_monitor.h"
#include "joystick_monitor.h"


///////////////////////////////////////////////////////////////////////////////
#define LED_BUILTIN 2

#define MIDI_CHANNEL 10
#define DEFAULT_VELOCITY 100

static const int POT_CC[3] = {20, 21, 22};
static const int JS_CC[2] = {24, 25};

static const int DEBOUNCE_TIME = 20;

static unsigned long t0 = millis();
static unsigned long t1[16] = {millis()};

static bool noteOn[16] = {0};

static bool isConnected = false;


///////////////////////////////////////////////////////////////////////////////
// BLEMIDI_CREATE_DEFAULT_INSTANCE();
BLEMIDI_CREATE_INSTANCE("checkerbeat_nimBLE", MIDI);


///////////////////////////////////////////////////////////////////////////////
void midi_setup();
// void pots_to_midi();
// bool js_changed(float, float);
// void joystick_to_midi();
bool debounce();
void buttons_to_midi(byte, byte);
void midi_handler();
void activity_led_off();


///////////////////////////////////////////////////////////////////////////////
void midi_setup() {
    MIDI.begin(MIDI_CHANNEL);

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    BLEMIDI.setHandleConnected([]() {
    isConnected = true;
    digitalWrite(LED_BUILTIN, HIGH);
    });

    BLEMIDI.setHandleDisconnected([]() {
    isConnected = false;
    digitalWrite(LED_BUILTIN, LOW);
    });

    MIDI.setHandleNoteOn([](byte channel, byte note, byte velocity) {
    digitalWrite(LED_BUILTIN, LOW);
    });

    MIDI.setHandleNoteOff([](byte channel, byte note, byte velocity) {
    digitalWrite(LED_BUILTIN, HIGH);
    });
}


void pots_to_midi() {
    for(int i = 1; i < 3; i++){
        if(pots[i] != prev_pots[i]) {
            MIDI.sendControlChange(POT_CC[i], pots[i], MIDI_CHANNEL);
            prev_pots[i] = pots[i];
        }
    }
}


// bool js_changed(float js, float prev_js) {
//     int js_threshold = 1/64;
//     if(js > prev_js * (1 + js_threshold)) return 1;
//     if(js < prev_js * (1 - js_threshold)) return 1;
//     return 0;
// }


void joystick_to_midi() {
//    if(js_changed(joystick_x, prev_joystick_x)) {
    if(joystick_x != prev_joystick_x) {
        // MIDI.sendPitchBend(joystick_x, MIDI_CHANNEL);
        // MIDI.sendControlChange(JS_CC[0], joystick_x, MIDI_CHANNEL); 
        prev_joystick_x = joystick_x;
    }
    if(joystick_y != prev_joystick_y) {
        MIDI.sendControlChange(JS_CC[1], joystick_y, MIDI_CHANNEL); 
        prev_joystick_y = joystick_y;
    }
}


bool debounce(int i) {
    if (millis() > (t1[i] + DEBOUNCE_TIME)) {return true;}
    return false;
}


void buttons_to_midi(byte shiftreg1, byte shiftreg2) {
    for(int i = 0; i < 16; i++) {
        if(i < 8) {
            if (shiftreg1 & 0x01 == 1) {
                if(!noteOn[i] && debounce(i)) {
                    noteOn[i] = true;
                    // SerialMIDI.sendNoteOn((BUTTON_MAP[i]), pots[0], MIDI_CHANNEL);
                    MIDI.sendNoteOn((BUTTON_MAP[i]), DEFAULT_VELOCITY, MIDI_CHANNEL);
                    digitalWrite(LED_BUILTIN, HIGH);
                    t0 = millis();
                    t1[i] = millis();
                }
            } else {
                if(noteOn[i] && debounce(i)) {
                    noteOn[i] = false;
                    MIDI.sendNoteOff((BUTTON_MAP[i]), 0, MIDI_CHANNEL);
                    t1[i] = millis();
                }
            }
            shiftreg1 = shiftreg1 >> 1;
        }
        if(i > 7) {
            if (shiftreg2 & 0x01 == 1) {
                if(!noteOn[i] && debounce(i)) {
                    noteOn[i] = true;
                    // SerialMIDI.sendNoteOn((BUTTON_MAP[i]), pots[0], MIDI_CHANNEL);
                    MIDI.sendNoteOn((BUTTON_MAP[i]), DEFAULT_VELOCITY, MIDI_CHANNEL);                    
                    digitalWrite(LED_BUILTIN, HIGH);
                    t0 = millis();
                    t1[i] = millis();
                }
            } else {
                if(noteOn[i] && debounce(i)) {
                    noteOn[i] = false;
                    MIDI.sendNoteOff((BUTTON_MAP[i]), 0, MIDI_CHANNEL);
                    t1[i] = millis();
                }
            }
            shiftreg2 = shiftreg2 >> 1;
        }
    }
}


void activity_led_off() {
    if((millis() - t0) > 50) digitalWrite(LED_BUILTIN, LOW);
}


void midi_handler() {
    buttons_to_midi(~buttons1, ~buttons2);
    // pots_to_midi();
    // joystick_to_midi();

    activity_led_off();
}
