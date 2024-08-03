#include <Adafruit_Fingerprint.h>
#include "Authenticate.h"
#include "Enroll.h"
#include "Delete.h"

#if (defined(__AVR__) || defined(ESP8266)) && !defined(__AVR_ATmega2560__)
#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3);
#else
#define mySerial Serial1
#endif

Adafruit_Fingerprint finger(&mySerial);
Authenticate auth(finger);
Enroll enroll(finger);
Delete del(finger);

// Function prototype
uint8_t readNumber();

void setup() {
    Serial.begin(9600);
    while (!Serial);
    delay(100);
    Serial.println("\n\nFingerprint System");

    finger.begin(57600);
    if (finger.verifyPassword()) {
        Serial.println("Found fingerprint sensor!");
    } else {
        Serial.println("Did not find fingerprint sensor :(");
        while (1) { delay(1); }
    }
}

void loop() {
    Serial.println("Select an option:");
    Serial.println("1. Enroll new fingerprint");
    Serial.println("2. Authenticate fingerprint");
    Serial.println("3. Delete fingerprint");
    Serial.println("4. Exit");

    uint8_t option = readNumber();
    switch (option) {
        case 1:
            enroll.enrollFingerprint();
            break;
        case 2:
            auth.authenticateFingerprint();
            break;
        case 3:
            del.deleteFingerprint();
            break;
        case 4:
            Serial.println("Exiting...");
            while (1); // Halt the program
            break;
        default:
            Serial.println("Invalid option, please try again.");
            break;
    }

    delay(1000); // Delay before showing the menu again
}

// Function definition
uint8_t readNumber() {
    uint8_t num = 0;
    while (num == 0) {
        while (!Serial.available());
        num = Serial.parseInt();
    }
    return num;
}
