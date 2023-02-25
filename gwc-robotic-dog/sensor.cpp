//
// Created by starchmd on 10/28/19.
//
#include <Arduino.h>
#include "sensor.hpp"

#define INTERRPUT_PIN 2

Sensor* Sensor::i_sensor = NULL;

Sensor::Sensor(Clock& clock, int pin) :
    m_clock(clock),
    m_pulse_time(0),
    m_last_reading(0),
    m_pin(pin)
{
    pinMode(pin, OUTPUT);
    pinMode(INTERRPUT_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(INTERRPUT_PIN), Sensor::isr, CHANGE);
    Sensor::i_sensor = this;
}

void Sensor::emit() {
    digitalWrite(m_pin, HIGH);
    delayMicroseconds(10); // Wait 10uS for pulse
    m_last_reading = 0;
    digitalWrite(m_pin, LOW);
    m_pulse_time = 0;
}

unsigned long Sensor::pulse() {
    return m_pulse_time;
}


void Sensor::isr() {
    unsigned long reading = micros();
    int stat = digitalRead(INTERRPUT_PIN);
    // Check if reading is zero, if so update
    if (Sensor::i_sensor->m_last_reading == 0) {
        Sensor::i_sensor->m_last_reading = reading;
    }
    // Check roll-over
    else if (Sensor::i_sensor->m_last_reading > reading) {
        Sensor::i_sensor->m_pulse_time = (reading + 1000000) - Sensor::i_sensor->m_last_reading;
    }
    // Normal non-rollover
    else {
        Sensor::i_sensor->m_pulse_time = reading - Sensor::i_sensor->m_last_reading;
    }
}
// D = 1/2 T * sound speed
