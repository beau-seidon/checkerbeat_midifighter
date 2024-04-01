#pragma once
#include <Arduino.h>

#include "button_monitor.h"
#include "pot_monitor.h"
#include "joystick_monitor.h"


///////////////////////////////////////////////////////////////////////////////
static const int SERIAL_BAUD = 9600;


///////////////////////////////////////////////////////////////////////////////
void serial_setup();
void serial_handler_btns(byte, byte);
void serial_handler_pots(int *pts);
void serial_handler_js(int *js);
void serial_delay();
void serial_handler();


///////////////////////////////////////////////////////////////////////////////
void serial_setup() {
    Serial.begin(SERIAL_BAUD);
}


void serial_handler_btns(byte shiftreg1, byte shiftreg2) {
    Serial.print("Pin States:\r\n");
    for(int i = 0; i < 16; i++) {
        if(i < 8) {
            if (shiftreg1 & 0x01 == 1) {
                Serial.print(1);
            } else {
                Serial.print(0);
            }
            shiftreg1 = shiftreg1 >> 1;
        }
        if(i == 8) Serial.print(" ");
        if(i > 7) {
            if (shiftreg2 & 0x01 == 1) {
                Serial.print(1);
            } else {
                Serial.print(0);
            }
            shiftreg2 = shiftreg2 >> 1;
        }
    }
    Serial.print("\r\n");
}


void serial_handler_pots(int *pts) {
    Serial.println("Pots:");
    for(int i=0; i<3; i++) {
        Serial.print(pts[i]);
        Serial.print(" ");
    }
    Serial.print("\n");
}


void serial_handler_js(int js_x, int js_y) {
    Serial.println("Joysticks:");
    Serial.print(js_x);
    Serial.print(" ");
    Serial.print(js_y);
    Serial.print("\n\n");
}


void serial_delay() {
    delay(1000);
}


void serial_handler() {
        serial_handler_btns(~buttons1, ~buttons2);
        serial_handler_pots(pots);
        serial_handler_js(joystick_x, joystick_y);
        serial_delay();
}
