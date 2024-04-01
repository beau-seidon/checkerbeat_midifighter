#include "button_monitor.h"



// 2 bytes to hold 16 button states
byte buttons1;
byte buttons2;


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
