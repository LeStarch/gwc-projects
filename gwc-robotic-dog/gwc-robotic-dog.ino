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
#include "motor.hpp"

//Note for Michael: A4, A5 appear to be I2C pins, 13 is used as LED, sensore uses 8 as trigger and 2 as interrupt back.  10, 11 are software serial pins.

// We choose output pin 6 to wire the speaker to. The negative lead should be tied to ground.
const unsigned int OUTPUT_PIN = 6;
const unsigned int SENSOR_PIN = 8;
// This helps our program keep time.
Clock runner;
Sensor sensor(runner, SENSOR_PIN);
Motor left(Motor::LEFT);
Motor right(Motor::RIGHT);

/**
 * !!! GWC START HERE !!!  You will also see "!!! GWC" notes below where you can explore in the code.
 * 
 * It is time to put everything together.  We have motors, sensors, speaker output and code.  Our goal is to make a robotic Dog that can sense the world
 * and respond.  It is up to you and your team to decide what this Dog will do, and how it will respond to the world.  Good luck!!! Ask questions!!!
 */
RecordedSound audio; // Use this one to play recorded audio

void setup() {
    // Hardware check
    pinMode(13, OUTPUT);
    digitalWrite(13, HIGH);
    Motor::init();
    // !!! GWC don't touch these lines, they setup the timing for the system.
    runner.init(SAMPLE_FREQUENCY);
    runner.register_clockable(audio, SAMPLE_FREQUENCY);
    runner.register_clockable(left, MOTOR_FREQUENCY);
    runner.register_clockable(right, MOTOR_FREQUENCY);

    // Initialize arduino sound objects.  They use the same pin. Start with no note.
    audio.init();
      while (true){
        audio.start(1);//bork
        runner.delay(10);
        left.setSpeed(Motor::M_REVERSE, 200.0);
        right.setSpeed(Motor::M_REVERSE, 200.0);
        sensor.emit();
        runner.delay(10);
        left.start();
        right.start();
        while (sensor.pulse()>30) {
          sensor.emit();
          runner.delay(10);
        }
        left.stop();
        right.stop();
        audio.start(2);
        runner.delay(5000);
        left.setSpeed(Motor::M_FORWARD, 200.0);
        right.setSpeed(Motor::M_REVERSE, 200.0);
        left.start();
        right.start();
        runner.delay(500);
        left.stop();
        right.stop();
        
      }
    
    //runner.delay(1000);
    //audio.start(2);

    //!!! GWC START HERE !!!
    //left.setSpeed(Motor::M_FORWARD, 200.0);
    //right.setSpeed(Motor::M_FORWARD, 200.0);
    //left.start();
    //runner.delay(1000);
    //left.stop();
    //right.start();
    //runner.delay(1000);
    //right.stop();
}

// Each call to "loop" is one iteration for the "loop forever" loop that we will run.
void loop() {
  delay(1000);
}
