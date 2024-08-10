#include "ServoControl.h"

ServoControl::ServoControl(int pin) : servoPin(pin) {
    myServo.attach(servoPin);
    myServo.write(defaultAngle); // Initialize to default angle (0 degrees)
}

void ServoControl::rotateOnSuccess() {
    myServo.write(successAngle); // Rotate to 90 degrees
    delay(delayTime);            // Wait for 5 seconds
    myServo.write(defaultAngle); // Return to 0 degrees
}
