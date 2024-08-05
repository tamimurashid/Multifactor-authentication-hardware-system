#ifndef ENROLL_H
#define ENROLL_H

#include <Adafruit_Fingerprint.h>

class Enroll {
public:
    Enroll(Adafruit_Fingerprint &fingerprintSensor);
    uint8_t getFingerprintEnroll();
    uint8_t enrollFingerprint();
    uint8_t generateRandomID();

private:
    Adafruit_Fingerprint &finger;
    uint8_t id;
    bool usedIDs[127]; // Array to keep track of used IDs
    uint8_t generateUniqueID();
    uint8_t readNumber();
};

#endif // ENROLL_H
