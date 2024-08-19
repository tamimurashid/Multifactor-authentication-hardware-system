/*
  This is the main file which execute to the micocontroller board 
  Created by talian robotics 

*/

/* This below are header files for the project */
#include <Adafruit_Fingerprint.h>
#include <Wire.h>
#include "Authenticate.h"
#include "Enroll.h"
#include "Delete.h"
#include "Indicator.h"
#include "LCD_Display.h"

#define SDA_PIN D2
#define SCL_PIN D1


#if (defined(__AVR__) || defined(ESP8266)) && !defined(__AVR_ATmega2560__)
#include <SoftwareSerial.h>
SoftwareSerial mySerial(13, 15);// for esp8266 this is pin no 8 and 7
// SoftwareSerial mySerial(2, 3); // for arduino board
#else
#define mySerial Serial1
#endif

/* Object creation or decralation frommthe class found in the provided header files */
Adafruit_Fingerprint finger(&mySerial);
Authenticate auth(finger);
Enroll enroll(finger);
Delete del(finger);
LCD_Display lcd(0x27, 16, 2);



// Function prototype
String readCommand();

void setup() {
    // pinMode(warning_led, OUTPUT);
    Serial.begin(9600);
    Wire.begin(SDA_PIN, SCL_PIN);// begin i2c commmunication 
    lcd.begin();// begin the lcd display 
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
    lcd.printMessage("Waiting for command...", 0);
    //lcd.printMessage("LCD Tutorial", 1);

    if (command == "ENROLL" || command == "enroll" || command == "2") {
        Serial.println("Starting enrollment...");
        lcd.printMessage("Starting enrollment...", 0);
        enroll.enrollFingerprint();
    } else if (command == "AUTH" || command == "A" || command == "a" || command == "1") {
        Serial.println("Entering continuous authentication mode.");
        lcd.printMessage("Entering continuous authentication mode.", 0);
        while (true) {
            auth.authenticateFingerprint();

            // Check for 'S' command to stop authentication mode
            if (Serial.available() > 0) {
                String stopCommand = readCommand();
                if (stopCommand == "S" || stopCommand == "s" || stopCommand == "0") {
                    Serial.println("Exiting authentication mode.");
                    lcd.printMessage("Exiting authentication mode..", 0);
                    break;
                }
            }
            delay(100); // Add a slight delay to prevent rapid looping
        }
    } else if (command == "DELETE" || command == "delete" || command == "4") {
        Serial.println("Starting deletion...");
        lcd.printMessage("Starting deletion...", 1);
        del.deleteFingerprint();
    } else if (command == "EXIT") {
        Serial.println("Exiting...");
         lcd.printMessage("Exiting..., Thankyou welcome again.", 0);
        while (1);
    } else {
        Serial.println("Invalid command, please try again.");
        lcd.printMessage("Invalid command, please try again.", 1);
    }

    delay(1000); 
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
