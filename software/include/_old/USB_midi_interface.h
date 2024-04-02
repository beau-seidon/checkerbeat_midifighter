// #pragma once

// #include <Arduino.h>

// #include <Adafruit_TinyUSB.h>
// // #include <arduino\midi\Adafruit_USBD_MIDI.h>
// #include <MIDI.h>
// // #include <USB-MIDI.h>

// #include "button_monitor.h"
// #include "pot_monitor.h"
// #include "joystick_monitor.h"


// #define LED_BUILTIN 2

// int low_note = 36;
// int velocity = 127;
// int midi_channel = 10;

// bool noteOn[16] = {0};

// unsigned long t0 = millis();


// // USBMIDI_CREATE_DEFAULT_INSTANCE();


// // USB MIDI object
// Adafruit_USBD_MIDI usb_midi;

// // Create a new instance of the Arduino MIDI Library,
// // and attach usb_midi as the transport.
// MIDI_CREATE_INSTANCE(Adafruit_USBD_MIDI, usb_midi, MIDI);


// void handleNoteOn(byte channel, byte pitch, byte velocity) {
//     // Log when a note is pressed.
//     // Serial.print("Note on: channel = ");
//     // Serial.print(channel);

//     // Serial.print(" pitch = ");
//     // Serial.print(pitch);

//     // Serial.print(" velocity = ");
//     // Serial.println(velocity);
// }

// void handleNoteOff(byte channel, byte pitch, byte velocity) {
//     // Log when a note is released.
//     // Serial.print("Note off: channel = ");
//     // Serial.print(channel);

//     // Serial.print(" pitch = ");
//     // Serial.print(pitch);

//     // Serial.print(" velocity = ");
//     // Serial.println(velocity);
// }

// void usb_setup() {
//     #if defined(ARDUINO_ARCH_MBED) && defined(ARDUINO_ARCH_RP2040)
//     // Manual begin() is required on core without built-in support for TinyUSB such as mbed rp2040
//     TinyUSB_Device_Init(0);
//     #endif

//     usb_midi.setStringDescriptor("ESP32_CheckerBeat");

//     // Initialize MIDI, and listen to all MIDI channels
//     // This will also call usb_midi's begin()
//     MIDI.begin(midi_channel);

//     // Attach the handleNoteOn function to the MIDI Library. It will
//     // be called whenever the Bluefruit receives MIDI Note On messages.
//     MIDI.setHandleNoteOn(handleNoteOn);

//     // Do the same for MIDI Note Off messages.
//     MIDI.setHandleNoteOff(handleNoteOff);

//     // wait until device mounted
//     while( !TinyUSBDevice.mounted() ) delay(1);
// }



// void midi_setup() {
//     pinMode(LED_BUILTIN, OUTPUT);
//     // MIDI.begin(midi_channel);
//     usb_setup();
// }

// void buttons_to_midi(byte shiftreg1, byte shiftreg2) {
//     for(int i = 0; i < 16; i++) {
//         if(i < 8) {
//             if (shiftreg1 & 0x01 == 1) {
//                 if(!noteOn[i]) {
//                     noteOn[i] = true;
//                     MIDI.sendNoteOn((i+low_note), velocity, midi_channel);
//                     digitalWrite(LED_BUILTIN, HIGH);
//                     t0 = millis();
//                 }
//             } else {
//                 if(noteOn[i]) {
//                     noteOn[i] = false;
//                     MIDI.sendNoteOff((i+low_note), 0, midi_channel);
//                 }
//             }
//             shiftreg1 = shiftreg1 >> 1;
//         }
//         if(i > 7) {
//             if (shiftreg2 & 0x01 == 1) {
//                 if(!noteOn[i]) {
//                     noteOn[i] = true;
//                     MIDI.sendNoteOn((i+low_note), velocity, midi_channel);
//                     digitalWrite(LED_BUILTIN, HIGH);
//                     t0 = millis();
//                 }
//             } else {
//                 if(noteOn[i]) {
//                     noteOn[i] = false;
//                     MIDI.sendNoteOff((i+low_note), 0, midi_channel);
//                 }
//             }
//             shiftreg2 = shiftreg2 >> 1;
//         }
//     }
// }

// void pots_to_midi() {

// };

// void joystick_to_midi() {

// };

// void midi_handler() {
//     buttons_to_midi(~buttons1, ~buttons2);
//     pots_to_midi();
//     joystick_to_midi();
//     if((millis() - t0) > 50) digitalWrite(LED_BUILTIN, LOW);
// }
