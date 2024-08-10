#ifndef SERVOCONTROL_H
#define SERVOCONTROL_H

#include <Servo.h>

class ServoControl {
public:
    ServoControl(int servoPin);
    void rotateOnSuccess();

private:
    Servo myServo;
    int servoPin;
    const int successAngle = 90;
    const int defaultAngle = 0;
    const unsigned long delayTime = 5000; // 5 seconds
};

#endif
