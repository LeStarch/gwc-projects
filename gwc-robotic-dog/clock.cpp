// Implementation for clock.hpp
//
// Created by starchmd on 10/11/19.
//
#include <Arduino.h>
#include "clock.hpp"

// Clock constructor
Clock::Clock() :
    m_tick_count(0),
    m_frequency(0),
    m_clock_period(0) {
    // Initialize to NULLS
    for (unsigned int i = 0; i < sizeof(m_clockables)/ sizeof(m_clockables[0]); i++) {
        m_clockables[i] = NULL;
        m_ticks[i] = 0;
    }
}

// Initialize the clock with a frequency
void Clock::init(unsigned int frequency) {
    m_frequency = frequency;
    m_clock_period = 1000000l/frequency;
    pinMode(13, OUTPUT);
}

// Registration interface for clockables
void Clock::register_clockable(Clockable& clockable, unsigned int frequency) {
    unsigned int ticks = m_frequency / frequency;
    // Find the first NULL and fill it
    for (unsigned int i = 0; i <sizeof(m_clockables)/ sizeof(m_clockables[0]); i++) {
        // Found an empty record, fill it and leave
        if (m_clockables[i] == NULL) {
            m_clockables[i] = &clockable;
            m_ticks[i] = ticks;
            break;
        }
    }
}

// Update all clockables
void Clock::update_all() {
    // Find the first NULL and fill it
    for (unsigned int i = 0; i < (sizeof(m_clockables) / sizeof(m_clockables[0])) && m_clockables[i] != NULL; i++) {
        // Check m_tick count if it ligns up, then "tick" the child
        if ((m_tick_count % m_ticks[i]) == 0) {
            m_clockables[i]->update();
        }
    }
    m_tick_count++;
}

// Process all clockables
void Clock::process_all() {
    // Find the first NULL and fill it
    for (unsigned int i = 0; i < (sizeof(m_clockables) / sizeof(m_clockables[0])) && m_clockables[i] != NULL; i++) {
        m_clockables[i]->process();
    }
}

// Delay and run at the same time
void Clock::delay(unsigned long milliseconds) {
    // Loop until we have waited long enough
    unsigned long end_millis = millis() + milliseconds;
    while (millis() < end_millis) {
        // How often do we play a sample
        unsigned long end_time = micros() + m_clock_period;
        process_all();
        // Sleep until the next output tick
        long sleep_time_us = end_time - micros();
        if (sleep_time_us > 2 && sleep_time_us < 32000) {
            //digitalWrite(13, LOW);
            delayMicroseconds(sleep_time_us);
        }
        else {
            digitalWrite(13, HIGH);
        }
        update_all();
    }
}
