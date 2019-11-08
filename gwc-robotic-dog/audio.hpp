/* audio.hpp:
 *
 * This file contains the necessary definitions for playing audio using our Arduino setup. It has been designed to
 * operate as a driven device needing to be driven at a set rate such that it can play a sound. This rate is the sample
 * rate of the audio it is playing.  Typically this rate should be 2x more that the highest frequency component of the
 * sound being played.
 *
 * Since the Arduino is a 5V digital device, the audio played will be a square wave. This wave is then threshold and
 * played on the speaker. Better audio could be achieved with analog circuits, however; that is outside the scope of the
 * lesson.
 *
 * **Usage:**
 * ```
 * ArduinoSound& sound = ...// Fill in reference with non-abstract subtype
 * sound.init(6, 8000);     // Output to pin 6, at a frequency of 8KHz
 * ...
 * // Every 100Hz
 * sound.play();
 * sound.prep_sample(); // Sets the next sample to play
 * ```
 * Created by starchmd on 10/11/19.
 */
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

#include "clock.hpp"
#include "sample.hpp"

class ArduinoSound : public Clockable {
    public:
        /**
         * Constructor used to initialize the ArduinoSound class. This constructor will only setup initialization on
         * memory, as it has a separate init function used to setup the electronics.
         */
        ArduinoSound();

        /**
         * Initialize the sound player. This will prepare the output signal digital pin. It will also setup the `m_freq`
         * variable, so users can generate sound should the desire to using that variable.
         * @param output_pin: output pin for producing sound output
         * @param freq: sample frequency for the output
         */
        virtual void init(int output_pin, int freq = 5000);

        /**
         * Used to calculate the next sample and queue it for playing. This is done as an update, because it could take
         * more time and should happen during the "work" phase of the project.
         */
        virtual void process();

        /**
         * Plays an individual sample and increases `m_played` by one. This allows users to use the m_played counter
         * to track the number of samples played. This is a fast write, performed on the clock-phase.
         */
        virtual void update();

        /**
         * This function must be implemented by sub-classes. The single job of this function is to return the next
         * sample that needs to be played.
         * \return next sample to play.
         */
        virtual unsigned char prep_sample() = 0;
    protected:
        unsigned int m_freq; // Frequency of sample generation. `play` will be called at his frequency.
    private:
        int m_output_pin; // Wire to outside world
        unsigned char m_sample; // Sample, written by prep_sample,
};

class RecordedSound : public ArduinoSound {
    public:
        // Constructor for recorded sound
        RecordedSound();
        /**
         * Plays an individual sample and increases `m_played` by one. This allows users to use the m_played counter
         * to track the number of samples played. This is a fast write, performed on the clock-phase.
         */
        virtual void update();

        /**
         * Preps a single sample to play. This should read one sample from storage and return it.
         */
        virtual unsigned char prep_sample();

        /**
         * Initializes the hardware required to run the sound-chip.
         */
        void init();

        /**
         * Resets and starts the playback. 
         */
        void start();
    private:
        SoftwareSerial m_serial;
        DFRobotDFPlayerMini m_player;
};


class ToneSound : public ArduinoSound {
    public:
        // Constructor for recorded sound
        ToneSound();
        /**
         * Plays an individual sample and increases `m_played` by one. This allows users to use the m_played counter
         * to track the number of samples played. This is a fast write, performed on the clock-phase.
         */
        virtual void update();

        /**
         * Preps a single sample to play. This should read one sample from storage and return it.
         */
        virtual unsigned char prep_sample();

        /**
         * Resets and starts the playback. 
         */
        void set_note(unsigned int freq);
    private:
        // Not freq converted to sample
        unsigned char sample_from_note(unsigned int note);
        unsigned long m_count;
        unsigned int m_note;
};

#ifndef GWC_ROBOTIC_DOG_AUDIO_HPP
#define GWC_ROBOTIC_DOG_AUDIO_HPP

#endif //GWC_ROBOTIC_DOG_AUDIO_HPP
