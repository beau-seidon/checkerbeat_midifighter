#pragma once
#include <Arduino.h>


///////////////////////////////////////////////////////////////////////////////
// SN74HC165 connections:
#define LOAD_PIN 12			// SH/LD (DIP PIN 1)
#define CLK_PIN 14			// CLK (DIP PIN 2)
#define DATA_PIN 27			// QH' (DIP PIN 7)
#define CLK_INH_PIN 26		// CLK INH (DIP PIN 15)

// 2 bytes to hold 16 button states
static byte buttons1;
static byte buttons2;

// this map is upside down
static const int BUTTON_MAP[16] = {	48, 46, 38, 45, 
       		                       	36, 37, 41, 40, 
									39, 47, 44, 49,
                            		43, 42, 50, 51 };


///////////////////////////////////////////////////////////////////////////////
void button_setup();
void button_handler();


///////////////////////////////////////////////////////////////////////////////
void button_setup() {
	pinMode(LOAD_PIN, OUTPUT);
	pinMode(CLK_INH_PIN, OUTPUT);
	pinMode(CLK_PIN, OUTPUT);
	pinMode(DATA_PIN, INPUT);
}


void button_handler() {
	digitalWrite(LOAD_PIN, LOW);
	delayMicroseconds(5);
	digitalWrite(LOAD_PIN, HIGH);
	delayMicroseconds(5);

	digitalWrite(CLK_PIN, HIGH);
	digitalWrite(CLK_INH_PIN, LOW);
	digitalWrite(CLK_PIN, LOW);
	buttons1 = shiftIn(DATA_PIN, CLK_PIN, MSBFIRST);
	buttons2 = shiftIn(DATA_PIN, CLK_PIN, MSBFIRST);
	digitalWrite(CLK_INH_PIN, HIGH);
}
