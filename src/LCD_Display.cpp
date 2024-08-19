#include "LCD_Display.h"

// Constructor implementation
LCD_Display::LCD_Display(uint8_t lcdAddr, uint8_t lcdCols, uint8_t lcdRows) 
    : lcd(lcdAddr, lcdCols, lcdRows) {}

// Initialize the LCD
void LCD_Display::begin() {
    lcd.begin(16, 2);  // Pass the number of columns and rows
    lcd.backlight();
}

// Print a message on a specific row
void LCD_Display::printMessage(const char* message, uint8_t row) {
    lcd.setCursor(0, row);
    lcd.print(message);
}
