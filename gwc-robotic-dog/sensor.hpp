//
// Created by starchmd on 10/28/19.
//

#ifndef GWC_ROBOTIC_DOG_SENSOR_HPP
#define GWC_ROBOTIC_DOG_SENSOR_HPP
#include "clock.hpp"

/**
 * Sensor:
 *
 * This class is used to handle sensor inputs. It will register an interrupt for the "response" line, and will send out
 * a trigger-pulse and then upon the recipt of the interrupt it will store the time of the pulse. Then the distance can
 * be estimated.
 *
 * @author lestarch
 */
class Sensor {
    public:
        /**
         * Class constructor.
         */
        Sensor(Clock& clock, int pin);
        /**
         * Start a message by emitting a 10uS pulse
         */
        void emit();
        /**
         * Last pulse time. This will return 0 if no reading has been returned.  Otherwise it will be the time of the
         * pulse's travel out and back. Use T * speed of sound * 0.5 to get distance. This function returns T.
         * @return time in microseconds.
         */
        unsigned long pulse();
        static Sensor* i_sensor; // Interrupted sensor
    private:
        /**
         * ISR function.  Gets return pulse.
         */
        static void isr();
        Clock& m_clock;
        volatile unsigned long m_pulse_time;
        unsigned long m_last_reading;
        int m_pin;
};

#endif //GWC_ROBOTIC_DOG_SENSOR_HPP
