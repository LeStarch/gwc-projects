/**
 * clock.hpp:
 *
 * The clock file sets up a class that can be used to handle multiple things at once. This allows our dog to both play
 * a sound and continue to run our program code. This allow the robot to move, sound, and react at all times.
 *
 * In order to do this, we have replaced the normal delay functions with our own implementations that spend time doing
 * work for all of the other components in the system.
 *
 * Created by starchmd on 10/11/19.
 */
#ifndef GWC_ROBOTIC_DOG_CLOCK_HPP
#define GWC_ROBOTIC_DOG_CLOCK_HPP
#define MAX_CLOCKABLES 10

class Clockable {
    public:
        /**
         * Function that is the clock-tick. This should be quick, and will dispatch to all items befor calling the longer
         * running process functions.
         */
        virtual void update() = 0;

        /**
         * Function that allows the system to do longer amounts of work when waiting between systems. This comes after the
         * clock-ticks have been dispatched to fill up down-time before waiting. This should *try* not to do anything that
         * takes a super-long time.
         */
        virtual void process() = 0;
};

class Clock
{
    public:
        // Clock constructor
        Clock();
        /**
         * Initialize this clock to a given frequency.
         */
        void init(unsigned int frequency);
        /**
         * Register a clockable instance to ensure that it tracked and run
         */
        void register_clockable(Clockable& clockable, unsigned int frequency);

        /**
         * Delays the program for a set amount of time in Milliseconds. This will continue to run the registere clocables
         * internally. This allows them to run while a delay is going on.
         * @param milliseconds: milliseconds to delay for
         */
        void delay(unsigned long milliseconds);
    private:
        /**
         * Update all the clockables
         */
        void update_all();
        /**
         * Process all clockables
         */
        void process_all();
        // Variable storage
        unsigned long m_tick_count;
        unsigned int m_frequency;
        unsigned int m_clock_period;
        Clockable* m_clockables[MAX_CLOCKABLES];
        unsigned int m_ticks[MAX_CLOCKABLES];
};

#endif //GWC_ROBOTIC_DOG_CLOCK_HPP
