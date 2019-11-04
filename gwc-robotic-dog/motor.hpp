#include <Wire.h>
#include <AccelStepper.h>
#include <Adafruit_MotorShield.h>
#include "clock.hpp"

#ifndef GWC_ROBOTIC_DOG_MOTOR_HPP
#define GWC_ROBOTIC_DOG_MOTOR_HPP

#define MOTOR_FREQUENCY 8000


class Motor : public Clockable {
    public:
      enum Orientation {
          LEFT = 0,
          RIGHT = 1
      };

      enum Direction {
          M_FORWARD = 1,
          M_REVERSE = -1
      };
            
      Motor(Orientation motor);
      void setSpeed(Direction direction, float speed);
      void start();
      void stop();
      void update();
      void process();
      

      static void init();

    private:
       bool m_running;
       AccelStepper& m_stepper;
};
#endif
