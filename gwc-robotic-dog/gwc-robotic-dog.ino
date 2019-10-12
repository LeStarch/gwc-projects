/**
 * gwc-robotic-dog.ino:
 * 
 * This is the gwc-robotic-dog.ino file. It stest up the program to run. 
 * 
 */

#include <Arduino.h>
#include "clock.hpp"
#include "audio.hpp"

// Variables in global space
const unsigned int OUTPUT_PIN = 6;
Clock runner;

/**
 * GWC START HERE!!!
 * 
 * ~~ A Tale of Two Projects ~~
 * 
 * Can you play recorded sounds on Arduino. Your goal is to experiment
 * 
 */




// Choose one of the below
RecordedSound audio;
//ToneSound audio;

void setup() {
    // Setup clock at given frequency and register clockables
    runner.init(SAMPLE_FREQUENCY);
    runner.register_clockable(audio, SAMPLE_FREQUENCY);
    // Initialize arduino sound objects.  They use the same pin.
    audio.init(OUTPUT_PIN, SAMPLE_FREQUENCY);
    // C and rest
    /** This block plays tones if you use the ToneSound version **/
    /*    
    audio.set_note(262);
    runner.delay(500);
    audio.set_note(0);
    runner.delay(100);
    // D and rest
    audio.set_note(294);
    runner.delay(500);
    audio.set_note(0);
    runner.delay(100);
    */
    /** This block plays recorded sound, if RecordedSound version is chosen **/
    audio.start();
    runner.delay(5000);
}

// loop forever function
void loop() {
    runner.delay(0xFFFFFFFFl);
}
