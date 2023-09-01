#include <Arduino.h>

#include "button_monitor.h"
// #include "pot_monitor.h"
// #include "joystick_monitor.h"
#include "midi_interface.h"
// #include "BLE_midi_interface.h"
// #include "USB_midi_interface.h"
// #include "serial_debug.h"


///////////////////////////////////////////////////////////////////////////////
bool debug = false;


///////////////////////////////////////////////////////////////////////////////
void setup() {
    button_setup();
    // pot_setup();
    // joystick_setup();

    // if(debug) {
    //     serial_setup();
    // } else {
        midi_setup();
    // }
}


void loop() {
    button_handler();
    // pot_handler();
    // joystick_handler();

    // if(debug) {
    //     serial_handler();
    // } else {
        midi_handler();
    // }
}
