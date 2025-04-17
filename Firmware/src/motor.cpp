#include "motor.h"

motor::motor(int motorPinA, int motorPinB, bool reversed) {
    if (!reversed) {
        this->motorPinA = motorPinA;
        this->motorPinB = motorPinB;
    }
    else {
        this->motorPinA = motorPinB;
        this->motorPinB = motorPinA;
    }

    pinMode(motorPinA, OUTPUT);
    pinMode(motorPinB, OUTPUT);
}

void motor::drive(int speed) {
    if (speed > 0) {
        analogWrite(motorPinB, 0);
        analogWrite(motorPinA, speed);
    }
    else if (speed < 0) {
        analogWrite(motorPinA, 0);
        analogWrite(motorPinB, -speed);
    }
    else {
        analogWrite(motorPinA, 0);
        analogWrite(motorPinB, 0);
    }
}