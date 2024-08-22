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

    lcd.printMessage("Hi there", 0);
    delay(1000); // Pause for a moment

    // Scroll "Welcome to" from right to left
    // lcd.scrollMessage("Welcome to ", "Error",  1);

    // Scroll "Fingerprint System" from right to left
    lcd.scrollMessage("Welcome to Authentication system", "talion's system",  1);
    
    

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
     lcd.clearMessage();
     lcd.printMessage("Waiting for", 0);
     lcd.printMessage("command...", 1);
    String command = readCommand();

    if (command == "ENROLL" || command == "enroll" || command == "2") {
        Serial.println("Starting enrollment...");
        lcd.clearMessage();
        // lcd.printMessage("Starting enrollment...", 0);
        lcd.scrollMessage("Starting enrollment...", "Registration..",  1);
        enroll.enrollFingerprint();
    } else if (command == "AUTH" || command == "A" || command == "a" || command == "1") {
        Serial.println("Entering continuous authentication mode.");
        lcd.clearMessage();
        lcd.printMessage("Authentication..", 0);
        lcd.printMessage("mode On progress", 1);
        while (true) {
            auth.authenticateFingerprint();

            // Check for 'S' command to stop authentication mode
            if (Serial.available() > 0) {
                String stopCommand = readCommand();
                if (stopCommand == "S" || stopCommand == "s" || stopCommand == "0") {
                    Serial.println("Exiting authentication mode.");
                    lcd.clearMessage();
                    lcd.scrollMessage("Exiting authentication mode..", "Termination..",  1);
                    break;
                }
            }
            delay(100); // Add a slight delay to prevent rapid looping
        }
    } else if (command == "DELETE" || command == "delete" || command == "4") {
        Serial.println("Starting deletion...");
        lcd.clearMessage();
        lcd.scrollMessage("Starting deletion...", "Deleting",  1);
        del.deleteFingerprint();
        // keypad functionality for delete 
        // rfid functionality for delete 
    } else if (command == "EXIT"  || command == "0") {
        Serial.println("Exiting...");
         lcd.clearMessage();
        //  lcd.printMessage("Exiting...", 0);
         lcd.scrollMessage("Thankyou welcome again.", "Goodbye",  1);
        while (1);
    } else {
        Serial.println("Invalid command, please try again.");
        lcd.clearMessage();
        lcd.scrollMessage("Invalid command, please try again.", "Error",  1);
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
