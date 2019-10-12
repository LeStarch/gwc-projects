/**
 * gwc-robotic-dog.ino:
 * 
 * This is the gwc-robotic-dog.ino file. It sets up the lessons for building a robotic dog. Today's lesson is dealing
 * with sound, so we can make the Dog bark, or play music. These lessons will continue in parts, so for today start
 * with the lesson found below.  Look for !!! GWC START HERE !!! and other !!! GWC notes!
 *
 * Cheers,
 *
 * Michael
 */
#include <Arduino.h>
#include "clock.hpp"
#include "audio.hpp"

// We choose output pin 6 to wire the speaker to. The negative lead should be tied to ground.
const unsigned int OUTPUT_PIN = 6;
// This helps our program keep time.
Clock runner;

/**
 * !!! GWC START HERE !!!  You will also see "!!! GWC" notes below where you can explore in the code.
 * 
 * ~~ A Tale of Two Projects ~~
 *
 * There are two ways we can experiment with sound for this project. The first is to play music from the notes we are
 * used to when we play instruments. These sounds can be calculated, and sent out to the speaker to play. The other way
 * to play music is to record it and replay the recording out through the speaker. We will explore both below.
 *
 * Note: your team should start with one or the option below. Each will be a decent lesson.
 *
 * Project 1: Playing Music from Notes
 *
 * In this project, we will use the "ToneSound" generator to play audio. This audio will be set using frequency to
 * represent notes. Each note, "A" "B" "C" etc is a set sound frequency.  We can ask the TonePlayer below to play notes
 * using these frequencies.  https://pages.mtu.edu/~suits/notefreqs.html has a list of notes and frequencies. '0' is
 * treated in this program as a special frequency that turns output off.
 *
 * To play a sound, we will first set the note, and they "delay" the program for the duration we'd like to play that
 * note.  Then we can set the `0` note to shut the output off (i.e. play a rest). The not will play continually play
 * as long as the clock is delaying, so we *must* turn off the output by inserting a `0` note.
 *
 * Example:
 * ```
 * ToneSound audio;
 * ...
 * audio.init(6, 8000); // Starts the audio at sample rate 8000 Hz. This is how fast the note will be sampled/played.
 * audio.set_note(262);  // Starts the audio at sample rate 8000 Hz. This is how fast the note will be sampled/played.
 * runner.delay(5000);  // Allow the note to play for 5000ms (5 seconds)
 * audio.set_note(0);   // Turn off output
 * ```
 *
 * That is all. Try playing notes, music, or symphonies...and have fun.
 *
 * Project 2: Playing Recorded Audio
 *
 * Playing audio for this lesson is fairly easy. We just need to tell the "RecordedSound" version of the audio to
 * "start" and delay the machine enough such that the sound finishes. That is all!! The tricky part is getting sound
 * onto the device. Here is an example of playing the sound.
 *
 * Example:
 * ```
 * RecordedSound audio;
 * ...
 * audio.init(6, SAMPLE_FREQUENCY); // Starts the audio at sample rate as specified in the external C++ file
 * audio.start();      // Start/restart the playback
 * runner.delay(5000); // Play the recording, giving it 5 seconds to complete.
 * ```
 *
 * The question now is "how can we get this sound onto the Arduino.  The Arduino does not have a file system, so we
 * cannot just download a file.  All it knows is code and data stored in that code. Thus, we need to record sound, save
 * it into our code, compile the code with the sound data, and send that to the Arduino.
 *
 * Recording the sound.  To do this we will use the application "QuickTime Player" on Mac. This will allow us to record
 * sounds and save them. You should keep the recording less than about 3.5 seconds in order to ensure we will not over
 * run the device.  You can trim the audio down, should you need to. Save your recording as a .m4a somewhere you can
 * find as we will encode it next.
 * Help recording: http://osxdaily.com/2014/04/03/record-sound-mac-easy-quicktime/
 *
 * Encoding the sound. Unfortunately for us, QuickTime saves sound as a compressed .m4a audio format. This is good for
 * digital editing, and saving space on your computer, but requires the computer to "decompress" the audio before it can
 * play. This is likely more work than our Arduino can do. We need the audio in a much more easy to read format.
 *
 * First open iTunes and then preferences. Click on the button labeled setup input encoding.  On the new window we need
 * to select a WAV format with MONO audio, 8bit sample size, and 8K sample frequency. This can be done by selecting WAV
 * format and then "Custom".  Once custom appears, set the previously mentioned settings.  Ask a mentor for help, or
 * follow the the link: https://support.apple.com/guide/itunes/convert-music-file-formats-itns2972/mac
 *
 * Next open your file in iTunes, and then use "File -> Convert -> WAV Version" to re-save that file in the correct
 * format. Next copy that file to the same directory as the code for today's lesson.  We are ready to generate code!
 *
 * Open Terminal on Mac and run the following command to enter the directory with your code. Typically a mentor can help
 * you do this quickly, as we know Terminal is new to y'all.
 *
 * Once you are there we will run the command "sound-to-cpp.py" passing it your WAV file.  It will open that file, read
 * out all the data for the sound, and auto-generate a C++ file with your data in a big array ready to play by our
 * player. You can rerun the arduino code above to try out your sound.
 *
 * Example, assumes you downloaded code to your Desktop, and assumes that your file is named "your-file.wav".
 * ```
 * cd ~/Desktop/gwc-robotic-dog/
 * ./sound-to-cpp.py your-file.wav
 *```
 *
 * Run upload and Arduino and see what happens.
 */
// !!!GWC - Chose one of these below. !!!
//ToneSound audio; // Use this to play tonal sounds (notes)
//RecordedSound audio; // Use this one to play recorded audio

void setup() {
    // !!! GWC don't touch these lines, they setup the timing for the system.
    runner.init(SAMPLE_FREQUENCY);
    runner.register_clockable(audio, SAMPLE_FREQUENCY);

    // Initialize arduino sound objects.  They use the same pin.
    audio.init(OUTPUT_PIN, SAMPLE_FREQUENCY);
    /** !!! GWC: This block plays tones if you use the ToneSound version.
     *           Uncomment these lines in order to play the example notes
     *           for the Tone project.
     */
    /*    
    // audio.set_note(262); // Starts the audio at sample rate 8000 Hz. This is how fast the note will be sampled/played.
    // runner.delay(5000);  // Allow the note to play for 5000ms (5 seconds)
    // audio.set_note(0);   // Turn off output
    /** !!! GWC: This block plays recorded sound, if RecordedSound version is chosen.
     *           Uncomment these lines to play 5 seconds of recorded audio. (Less if the recording is shorter. This
     *           will play the pre-recorded audio, if you have not complete the lesson above.
     */
    //audio.start();      // Start/restart the playback
    //runner.delay(5000); // Play the recording, giving it 5 seconds to complete.
}

// This function will keep playing whatever was set forever.  TURN OFF NOTES before this!!!!! (Otherwise your mentors
// may lose sanity.)  Listening to any note forever is not fun.
void loop() {
    runner.delay(0xFFFFFFFFl);
}
