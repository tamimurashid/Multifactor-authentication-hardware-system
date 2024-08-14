#include "Authenticate.h"
#include <Arduino.h>
#include "Indicator.h"
#include "ServoControl.h"
#include "Lock.h"
const int trigger = 12;
const int servoPin = 16;
const int ledPin1 = 5; 
const int ledPin2 = 4; 
const unsigned long warningDelay = 1000;  
const unsigned long successDelay = 1000; 
const unsigned long  backresponse = 5000; // this is the delay for returning back the lock after being triggered 

Lock lock(trigger, backresponse);
Indicator indicator(ledPin1, ledPin2,  warningDelay, successDelay);
ServoControl servoControl(servoPin);
Authenticate::Authenticate(Adafruit_Fingerprint &fingerprintSensor) : finger(fingerprintSensor) {}

uint8_t Authenticate::getFingerprintID() {
    uint8_t p = finger.getImage();
    switch (p) {
        case FINGERPRINT_OK:
            Serial.println("Image taken");
            //delay(1000);
            break;
        case FINGERPRINT_NOFINGER:
            Serial.println("No finger detected");
            return p;
        case FINGERPRINT_PACKETRECIEVEERR:
            Serial.println("Communication error");
            indicator.error();
            delay(1000);
            return p;
        case FINGERPRINT_IMAGEFAIL:
            Serial.println("Imaging error");
            indicator.error();
            delay(1000);
            return p;
        default:
            Serial.println("Unknown error");
            indicator.error();
            delay(1000);
            return p;
    }

    p = finger.image2Tz();
    switch (p) {
        case FINGERPRINT_OK:
            Serial.println("Image converted");
            //delay(1000);
            break;
        case FINGERPRINT_IMAGEMESS:
            Serial.println("Image too messy");
            delay(1000);
            return p;
        case FINGERPRINT_PACKETRECIEVEERR:
            Serial.println("Communication error");
            indicator.error();
            delay(1000);
            return p;
        case FINGERPRINT_FEATUREFAIL:
            Serial.println("Could not find fingerprint features");
            indicator.error();
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
        indicator.success();
        //servoControl.rotateOnSuccess();
        lock.Open();
        return finger.fingerID;
      
    } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
        Serial.println("Communication error");
         indicator.error();
        return p;
    } else if (p == FINGERPRINT_NOTFOUND) {
        Serial.println("Did not find a match");
         indicator.error();
        return p;
    } else {
        Serial.println("Unknown error");
        return p;
    }
}

uint8_t Authenticate::authenticateFingerprint() {
    return getFingerprintID();
}
