/**
 * gwc-robotic-dog.ino:
 * 
 * This is the gwc-robotic-dog.ino file. It sets up the lessons for building a robotic dog. Today's lesson is dealing
 * with sensors, so we can make the Dog bark, or play music to a changing world. These lessons will continue in parts,
 * so for today start with the lesson found below.  Look for !!! GWC START HERE !!! and other !!! GWC notes!
 *
 * Cheers,
 *
 * Michael
 */
#include <Arduino.h>
#include "clock.hpp"
#include "audio.hpp"
#include "sensor.hpp"

// We choose output pin 6 to wire the speaker to. The negative lead should be tied to ground.
const unsigned int OUTPUT_PIN = 6;
const unsigned int SENSOR_PIN = 8;
// This helps our program keep time.
Clock runner;
Sensor sensor(runner, SENSOR_PIN);

/**
 * !!! GWC START HERE !!!  You will also see "!!! GWC" notes below where you can explore in the code.
 * 
 * -- Sensors: Ultrasonic Distance Sensor (Echolocation) --
 * 
 * Ultrasound sensors emit a series of high-frequency sound pulses. These pulses will go out in the world and
 * reflect against objects and return to the sensor. The travel time is then measured and the distance is proportional
 * to the speed of sound in the air. This is roughly: distance = time / speed of sound.
 * 
 * First, we must call "sensor.emit();" to start the pulses. The sound will then travel through the air and reflect
 * back. The sensor will then raise a wire "high" for the time the pulse traveled. This is in the Sensor class and
 * the result from the last sensing is gotten with "unsigned long reading = sensor.pulse();" Thus we can ask the sensor
 * for the time (in microseconds) the sound took to travel. A 0 means: no reflection or too-far away.
 * 
 * Note: "runner.delay(10);" should be called to let the sound travel, otherwise we'll read the result before
 * the return wave and get 0 for "too-far" because "sensor.pulse();" returns 0 on "too far" and no-reading. 
 * 
 * ```
 * sensor.emit();
 * runner.delay(10); // Wait for a pulse up to 1.5 meters, before bailing
 * int reading = sensor.pulse();
 * ```
 * 
 * !!! GWC: Class Goal !!!
 * 
 * Today our goal is to take a reading (above) and play a sound when the user gets "close" (closer than 30cm).
 * Use the code above to get a reading, then build an "if" statement to play a note when true. You'll need to
 * convert from time in microseconds to distance.  The datasheet for the sensor is below, for reference. 
 * 
 * https://cdn.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf
 */
ToneSound audio; // Use this to play tonal sounds (notes)
//RecordedSound audio; // Use this one to play recorded audio

void setup() {
    // Hardware check
    pinMode(13, OUTPUT);
    digitalWrite(13, HIGH);
    // !!! GWC don't touch these lines, they setup the timing for the system.
    runner.init(SAMPLE_FREQUENCY);
    runner.register_clockable(audio, SAMPLE_FREQUENCY);

    // Initialize arduino sound objects.  They use the same pin. Start with no note.
    audio.init(OUTPUT_PIN, SAMPLE_FREQUENCY);
    audio.set_note(0);
}

// Each call to "loop" is one iteration for the "loop forever" loop that we will run.
void loop() {
    // Emit a pulse and wait for return register
    sensor.emit();
    runner.delay(10); // Wait for a pulse up to 1.5 meters, before bailing
    int reading = sensor.pulse();
    /* !!! GWC: implement this if statement to trigger the sensor
    if (???) {
        audio.set_note(262); // Play middle C
    }
    else {
       // ???
    }
    */
    // Delay for 1/2 second before sensing again
    runner.delay(500);
}
