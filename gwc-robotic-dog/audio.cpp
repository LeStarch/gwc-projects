// audio.cpp:
//
// This file contains the implementations for the definitions found in audio.hpp. More information is available in the
// header file.
//
// Created by starchmd on 10/11/19.
//
#include <Arduino.h>
#include "audio.hpp"

ArduinoSound :: ArduinoSound() :
    m_output_pin(-1),
    m_freq(1),
    m_sample(0)
{}

// Initialize the member variables of the Arduino sound
void ArduinoSound :: init(int output_pin, int freq) {
    m_output_pin = output_pin;
    m_freq = freq;
    m_sample = 0;
    // Set the pin mode, to be digital output
    pinMode(m_output_pin, OUTPUT);
}

// Preps the sample by "queuing" it in the one-deep output queue
void ArduinoSound :: process() {
    m_sample = prep_sample();
}

// Just send out data, quickly. This takes our sample, runs a threshold algorithm to build the square-wave
void ArduinoSound :: update() {
    if (m_sample != 0) {
        digitalWrite(m_output_pin, m_sample > 128);
    }
}

// Setup the recorded sample player
RecordedSound::RecordedSound() :
    ArduinoSound(),
    m_count(SAMPLE_COUNT) {}

// Update the samples played count
void RecordedSound::update() {
    // PLay only to the end
    if (m_count < SAMPLE_COUNT) {
      m_count++;
    }
    ArduinoSound::update();
}
// Play samples
unsigned char RecordedSound :: prep_sample() {
    unsigned char sample = pgm_read_byte_near(SAMPLES + m_count);
    if (m_count >= SAMPLE_COUNT) {
        return 0;
    }
    return sample;
}
// Start recorded sound item
void RecordedSound::start() {
    m_count = 0;
}



// Setup the tone generator
ToneSound::ToneSound() :
    ArduinoSound(),
    m_count(SAMPLE_COUNT),
    m_note(0) {}

// Update the samples played count
void ToneSound::update() {
    // PLay only to the end
    m_count++;
    ArduinoSound::update();
}

// Set the note and the duration
void ToneSound::set_note(unsigned int note) {
    m_note = note;
    m_count = 0;
}
// Process the sample prep
unsigned char ToneSound::prep_sample() {
    // No-note does not play
    if (m_note == 0) {
      return 0;
    }
    unsigned int ticks = m_freq / m_note;
    if (m_count % ticks <= ticks/2) {
        return 255;
    } else {
        return 1;
    }
}

//    unsigned int part = (note * m_count * 2 * 3);  //pi is exactly 3
//    return (unsigned char)(128.0f * sin((float)part/(float)m_freq));
