#ifndef DELETE_H
#define DELETE_H

#include <Adafruit_Fingerprint.h>

class Delete {
public:
    Delete(Adafruit_Fingerprint &fingerprintSensor);
    void deleteFingerprint();
private:
    Adafruit_Fingerprint &finger;
    uint8_t readNumber();
};

#endif
