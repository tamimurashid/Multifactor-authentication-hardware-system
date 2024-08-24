#ifndef ENROLL_H
#define ENROLL_H

#include <Adafruit_Fingerprint.h>

#define MAX_ID 127 // Define the maximum ID value

class Enroll {
public:
    Enroll(Adafruit_Fingerprint &fingerprintSensor);
    uint8_t enrollFingerprint();
private:
    uint8_t getUserInputID();       // Function to get user input for the ID
    uint8_t getFingerprintEnroll();

    Adafruit_Fingerprint &finger;   // Reference to the fingerprint sensor
    uint8_t id;                     // The ID for the fingerprint
    bool usedIDs[MAX_ID];           // Array to keep track of used IDs
};

#endif
