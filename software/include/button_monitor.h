#pragma once

#include <Arduino.h>



// SN74HC165 connections:
#define LOAD_PIN 12         // SH/LD (DIP PIN 1)
#define CLK_PIN 14          // CLK (DIP PIN 2)
#define DATA_PIN 27         // QH' (DIP PIN 7)
#define CLK_INH_PIN 26      // CLK INH (DIP PIN 15)


// this map is upside down
const int BUTTON_MAP[16] = {
    48, 46, 38, 45,
    36, 37, 41, 40,
    39, 47, 44, 49,
    43, 42, 50, 51
};


extern byte buttons1;
extern byte buttons2;

void button_setup(void);
void button_handler(void);
