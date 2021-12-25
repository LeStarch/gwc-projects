//////////////////////////////////////////////////
//////// GWC LESSON: Scroll To The Bottom ////////
//////////////////////////////////////////////////

/**
 * ArduinoAudio:
 *
 * This is the class used as an aurio player. It wraps an output pin and
 * plays audio via that output pin. It defines several methods for playing
 * audio including:
 *
 * Note: this class *is not* defined in standard C++ style.  It instead uses
 * a Java-like style for writing the class. The reason for this is that C++
 * classes are *usually* defined in 2 separate files.  However, here given this
 * lesson, we have defined it all in one file, and thus it looks more Java-like.
 */
class ArduinoAudio {
    public:
        /**
         * Construct this audio player. This takes a pin, and sets it to output
         * mode, so it can be turned on/off fast enough to make music.
         * \param int pin: pin to use as output. Plug th + line of the speaker here.
         */
        ArduinoAudio(int pin) {
            this->m_period_micros = 0;
            this->m_pin = pin;
            pinMode(this->m_pin, OUTPUT);
        }
        /**
         * Play a not (frequency) for a given duration.
         * \param float freq: frequency in HZ that is to be played
         * \param int duration: duration to play note. This is in milliseoncds.
         */
        void play_note(float freq, int duration) {
            unsigned long end_time = millis() + duration;
            m_period_micros = get_period_micros(freq);
            while (end_time >= millis()) {
                play();
            }
        }
        /**
         * Set the note (frequency) to be played, but don't block or wait for it to play.
         * This allows for external duration control, like a button or something.
         * \param float: frequency to set.
         */
        void set_note(float freq) {
            m_period_micros = get_period_micros(freq);
        }
        /**
         * Get the period (in microseconds) from the frequency
         * \param float freq: frequency in Hz 
         * \return: period in microseconds
         */
        unsigned int get_period_micros(float freq) {
            //1/fr * 1000000 is period in micro-seconds
            return (unsigned int)(1000000.0f/freq);
        }
        /**
         * A function used to play the music. Call this as often as possible to ensure
         * high music quality.
         */
        void play() {
            //Zero is an invalid half-period, so return and play nothing.
            //As is a period that is not divisible in 2 parts.
            if (m_period_micros < 2) {
                return;
            }
            //Get the current time in micro seconds from the start of this period
            unsigned int micro = micros() % m_period_micros;
            //Get a half-period fast by using shift to divide by 2
            unsigned int half_period = m_period_micros >> 1;
            //Calculate the triangle wave
            unsigned int analog = ((micro % half_period)* 256)/half_period;
            //The scond half of the period is off
            if (micro >= half_period) {
                analogWrite(this->m_pin, 258-analog);
            } else {
                analogWrite(this->m_pin, analog);
            }
        }
    private:
        //Local storage for the pin we use
        int m_pin;
        //The system plays notes based on their period in microseconds. Thus, we store
        //the period, not the frequency to avoid repeating maths.
        unsigned int m_period_micros;
};
//Define a global variable here that will be our audio player
//it is accesible from everywhere.
//Note: we pass it pin "A1" as the output pin for our audio.
ArduinoAudio player(A1);







////////////////////////////////////////////////
//////// GWC LESSON: Lesson Begins Here ////////
////////////////////////////////////////////////

// The above code is designed to support this project, but it shouldn't need to be touched.
// To explore, edit the below lines in order to design your own stuff.

//If you want yor music to play once, put it here.  Otherwise, put it
//in the loop function.
void setup() {
    //Play three notes at 100Hz
    player.play_note(100.0f, 200);
    player.play_note(0, 200);
    player.play_note(100.0f, 200);
    player.play_note(0, 200);
}


//If you want yor music to play in a loop, put it here.  Otherwise, put it
//in the setup function.
void loop() {
    //Beep at 2000.0Hz
    player.play_note(2000.0f, 200);
    player.play_note(0, 200);

    //Shutoff after several iterations. This is for your mentor's sanity.  Disable with
    //caution.
    static int counter = 0;
    if (counter >= 2) {
        while (1) {}
    }
    counter += 1;
}
