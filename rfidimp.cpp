#include <Arduino.h>
#include "Rfid.h"

// Define the RFID pins based on your connections
#define SS_PIN 4   // SDA/SS connected to GPIO4 (SC)
#define RST_PIN 2  // RST pin connected to GPIO2 (D4)
#define SCK_PIN 14 // SCK connected to GPIO14 (D5)
#define MOSI_PIN 13 // MOSI connected to GPIO13 (D4)
#define MISO_PIN 12 // MISO connected to GPIO12 (D6)

// Create an instance of the Rfid class with your defined pins
Rfid rfid(SS_PIN, RST_PIN);

void setup() {
    Serial.begin(115200);
    rfid.begin();  // Initialize the RFID reader

    Serial.println("RFID reader initialized.");
}

void loop() {
    // Check if an RFID card is present
    if (rfid.checkForCard()) {
        // Get the UID of the card
        String uid = rfid.getUID();
        Serial.print("Card detected! UID: ");
        Serial.println(uid);
    } else {
        Serial.println("No card detected.");
    }

    delay(1000);  // Delay for a second before checking again
}

