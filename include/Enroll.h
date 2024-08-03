#ifndef ENROLL_H
#define ENROLL_H

#include <Adafruit_Fingerprint.h>

class Enroll {
public:
     
    Enroll(Adafruit_Fingerprint &fingerprintSensor);
    uint8_t getFingerprintEnroll();
    uint8_t enrollFingerprint();
    

private:
    Adafruit_Fingerprint &finger;
    uint8_t id;
    uint8_t readNumber();
};

#endif // ENROLL_H
