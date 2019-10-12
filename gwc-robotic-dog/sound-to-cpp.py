#!/usr/bin/env python
"""
sound-to-cpp.py:

This file will read a supplied WAV sound file and convert it into the C++ code we can compile with Arduino. This will
allow you to generate the C++ code from the WAV file, effectively hiding this file in program memory.

@author Michael
"""

from __future__ import print_function
import os
import sys
import struct
import wave

MAX_SAMPLE_SIZE = 30000
SAMPLES_PER_LINE = 30
WAVE_HEADER = b"RIFF9WAVEfmt"
EXPECTED_HZ = 8000

def write_cpp(wav_path, freq, data):
    """
    Write the CPP file next to the WAV file including two variable definitions: SAMPLE_FREQ and SAMPLES[].
    :param wav_path: path to wav file.
    :param freq: frequency of WAV samples.
    :param data: data to write out
    """
    cpp_file = wav_path.replace(".wav", "").replace("WAV", "") + ".cpp"
    print("[INFO] Writing {} WAV samples to C++ file {}".format(len(data), cpp_file))
    with open(cpp_file, "w") as out_file:
        out_file.write("/* AUTO-GENERATED: Use CAUTION when editing. */\n")
        out_file.write("#include \"sample.hpp\"")
        out_file.write("\n\n")
        out_file.write("const unsigned int SAMPLE_FREQUENCY = {};\n".format(int(freq)))
        out_file.write("const unsigned int SAMPLE_COUNT = {};\n".format(len(data)))
        out_file.write("const unsigned char PROGMEM SAMPLES[] = {")
        # For each byte, write it into the array
        for index, byte in enumerate(data):
            if index % SAMPLES_PER_LINE == 0:
                out_file.write("\n    ")
            out_file.write("{:3}, ".format(ord(byte)))
        out_file.write("\n};\n")

def usage():
    """
    Print usage and exit.
    """
    print("Usage:\n\t{} WAV-FILE".format(sys.argv[0], file=sys.stderr))

def main(args):
    """
    Main function, takes on command line argument and produces a C++ file of the same name containing samples.
    """
    # Harvest user supplied arguments including the file path, or error if not supplied
    file_path = args[-1]
    if len(args) < 2 or not os.path.exists(file_path):
        print("[ERROR] Please supply .wav file as input.")
        usage() 
        return 2
    # Prepare to read a WAV file
    wav = None
    try:
        wav = wave.open(file_path)
        chans = wav.getnchannels()
        (chan_count, width, framerate, count, _, _) = wav.getparams()
        # Check for errors in format. Arduino cannot support MONO nor large sample size.
        if chan_count > 1:
            raise Exception("Stereo sound is invalid. Set converter to MONO.")
        elif width > 1:
            raise Exception("Sample width too-large. Set converter to 8bit.")
        elif count >= MAX_SAMPLE_SIZE:
            print("[WARN] {} samples is too-many. Truncating to {}".format(count, MAX_SAMPLE_SIZE))
        # Read raw data and write out CPP data
        data = wav.readframes(min(MAX_SAMPLE_SIZE, count))
        write_cpp(file_path, framerate, data)
    except Exception as exc:
        print("[ERROR] Invalid WAV file: {}".format(str(exc)), file=sys.stderr)
        return 1
    finally:
        # Close if open
        if wav is not None:
            wav.close()
    return 0

if __name__ == "__main__":
    sys.exit(main(sys.argv))
