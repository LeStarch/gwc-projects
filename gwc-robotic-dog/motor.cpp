#include "motor.hpp"


// Define the motor shield object
Adafruit_MotorShield s_shield(0x60);
Adafruit_StepperMotor* s_left = s_shield.getStepper(200, 2);
Adafruit_StepperMotor* s_right = s_shield.getStepper(200, 1);

#define STEP_TYPE SINGLE

void left_forward() {
    s_left->onestep(FORWARD, STEP_TYPE);
}

void left_backward() {
    s_left->onestep(BACKWARD, STEP_TYPE);
}

void right_forward() {
    s_right->onestep(BACKWARD, STEP_TYPE);
}

void right_backward() {
    s_right->onestep(FORWARD, STEP_TYPE);
}


AccelStepper s_acc_left(left_forward, left_backward);
AccelStepper s_acc_right(right_forward, right_backward);

Motor::Motor(Motor::Orientation motor) :
    m_running(false),
    m_stepper((motor == LEFT) ? s_acc_left : s_acc_right)
{}

void Motor::init() {
    s_shield.begin();
    s_acc_left.setMaxSpeed(1000.0f);
    s_acc_right.setMaxSpeed(1000.0f);
}

void Motor::setSpeed(Direction direction, float speed) {
    m_stepper.setSpeed((double)(direction) * speed);
}

void Motor::start() {
    m_running = true;
}

void Motor::stop() {
    m_running = false;
}

void Motor::process() {
    this->update();
}
void Motor::update() {
    if (m_running) {
        m_stepper.runSpeed();
    }
}
