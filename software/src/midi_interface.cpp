#include "midi_interface.h"



unsigned long Ta = millis();             // activity LED timer
unsigned long Tb[16] = {millis()};       // button debounce timers
unsigned long Tp[3] = {millis()};        // pot gate timers
unsigned long Tj[2] = {millis()};        // joystic gate timers

bool noteOn[16] = {0};



MIDI_CREATE_INSTANCE(HardwareSerial, Serial2, midi2);


void midi_setup() {
    midi2.begin(MIDI_CHANNEL);

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
}


bool debounce(int i) {
    if (millis() > (Tb[i] + DEBOUNCE_TIME)) {return true;}
    return false;
}


void buttons_to_midi(byte shiftreg1, byte shiftreg2) {
    for(int i = 0; i < 16; i++) {
        if(i < 8) {
            if (shiftreg1 & 0x01 == 1) {
                if(!noteOn[i] && debounce(i)) {
                    noteOn[i] = true;
                    midi2.sendNoteOn((BUTTON_MAP[i]), DEFAULT_VELOCITY, MIDI_CHANNEL);
                    digitalWrite(LED_BUILTIN, HIGH);
                    Ta = millis();
                    Tb[i] = millis();
                }
            } else {
                if(noteOn[i] && debounce(i)) {
                    noteOn[i] = false;
                    midi2.sendNoteOff((BUTTON_MAP[i]), 0, MIDI_CHANNEL);
                    Tb[i] = millis();
                }
            }
            shiftreg1 = shiftreg1 >> 1;
        }
        if(i > 7) {
            if (shiftreg2 & 0x01 == 1) {
                if(!noteOn[i] && debounce(i)) {
                    noteOn[i] = true;
                    midi2.sendNoteOn((BUTTON_MAP[i]), DEFAULT_VELOCITY, MIDI_CHANNEL);
                    digitalWrite(LED_BUILTIN, HIGH);
                    Ta = millis();
                    Tb[i] = millis();
                }
            } else {
                if(noteOn[i] && debounce(i)) {
                    noteOn[i] = false;
                    midi2.sendNoteOff((BUTTON_MAP[i]), 0, MIDI_CHANNEL);
                    Tb[i] = millis();
                }
            }
            shiftreg2 = shiftreg2 >> 1;
        }
    }
}


void activity_led_off() {
    if((millis() - Ta) > 50) digitalWrite(LED_BUILTIN, LOW);
}


void midi_handler() {
    buttons_to_midi(~buttons1, ~buttons2);
    // pots_to_midi();
    // joystick_to_midi();

    activity_led_off();
}


/*
void pots_to_midi() {
    for(int i = 1; i < 3; i++){
        if(pots[i] != prev_pots[i]) {
            midi2.sendControlChange(POT_CC[i], pots[i], MIDI_CHANNEL);
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
        // midi2.sendPitchBend(joystick_x, MIDI_CHANNEL);
        // midi2.sendControlChange(JS_CC[0], joystick_x, MIDI_CHANNEL);
        prev_joystick_x = joystick_x;
    }
    if(joystick_y != prev_joystick_y) {
        midi2.sendControlChange(JS_CC[1], joystick_y, MIDI_CHANNEL);
        prev_joystick_y = joystick_y;
    }
}
*/
