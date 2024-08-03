#include "Authenticate.h"
#include <Arduino.h>

Authenticate::Authenticate(Adafruit_Fingerprint &fingerprintSensor) : finger(fingerprintSensor) {}

uint8_t Authenticate::getFingerprintID() {
    uint8_t p = finger.getImage();
    switch (p) {
        case FINGERPRINT_OK:
            Serial.println("Image taken");
            delay(1000);
            break;
        case FINGERPRINT_NOFINGER:
            Serial.println("No finger detected");
            delay(1000);
            return p;
        case FINGERPRINT_PACKETRECIEVEERR:
            Serial.println("Communication error");
            delay(1000);
            return p;
        case FINGERPRINT_IMAGEFAIL:
            Serial.println("Imaging error");
            delay(1000);
            return p;
        default:
            Serial.println("Unknown error");
            delay(1000);
            return p;
    }

    p = finger.image2Tz();
    switch (p) {
        case FINGERPRINT_OK:
            Serial.println("Image converted");
            delay(1000);
            break;
        case FINGERPRINT_IMAGEMESS:
            Serial.println("Image too messy");
            delay(1000);
            return p;
        case FINGERPRINT_PACKETRECIEVEERR:
            Serial.println("Communication error");
            delay(1000);
            return p;
        case FINGERPRINT_FEATUREFAIL:
            Serial.println("Could not find fingerprint features");
            delay(1000);
            return p;
        case FINGERPRINT_INVALIDIMAGE:
            Serial.println("Could not find fingerprint features");
            delay(1000);
            return p;
        default:
            Serial.println("Unknown error");
            delay(1000);
            return p;
    }

    p = finger.fingerSearch();
    if (p == FINGERPRINT_OK) {
        Serial.println("Found a print match!");
        Serial.print("Found ID #"); Serial.print(finger.fingerID);
        Serial.print(" with confidence of "); Serial.println(finger.confidence);
        return finger.fingerID;
    } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
        Serial.println("Communication error");
        return p;
    } else if (p == FINGERPRINT_NOTFOUND) {
        Serial.println("Did not find a match");
        return p;
    } else {
        Serial.println("Unknown error");
        return p;
    }
}

uint8_t Authenticate::authenticateFingerprint() {
    return getFingerprintID();
}
