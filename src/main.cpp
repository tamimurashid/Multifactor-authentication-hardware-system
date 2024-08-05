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
String readCommand();

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
    Serial.println("Waiting for command...");
    String command = readCommand();

    if (command == "ENROLL" || command == "enroll" || command == "2") {
        Serial.println("Starting enrollment...");
        enroll.enrollFingerprint();
    } else if (command == "AUTH" || command == "A" || command == "a" || command == "1") {
        Serial.println("Entering continuous authentication mode.");
        while (true) {
            auth.authenticateFingerprint();

            // Check for 'S' command to stop authentication mode
            if (Serial.available() > 0) {
                String stopCommand = readCommand();
                if (stopCommand == "S" || stopCommand == "s" || stopCommand == "0") {
                    Serial.println("Exiting authentication mode.");
                    break;
                }
            }
            delay(100); // Add a slight delay to prevent rapid looping
        }
    } else if (command == "DELETE" || command == "delete" || command == "4") {
        Serial.println("Starting deletion...");
        del.deleteFingerprint();
    } else if (command == "EXIT") {
        Serial.println("Exiting...");
        while (1); // Halt the program
    } else {
        Serial.println("Invalid command, please try again.");
    }

    delay(1000); // Delay before processing the next command
}

// Function definition
String readCommand() {
    String command = "";
    while (command.length() == 0) {
        if (Serial.available() > 0) {
            command = Serial.readStringUntil('\n');
            command.trim(); // Remove any whitespace or newline characters
            Serial.flush(); // Flush the serial buffer to clear any additional data
        }
    }
    return command;
}
