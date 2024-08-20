#ifndef LCD_DISPLAY_H
#define LCD_DISPLAY_H

#include <LiquidCrystal_I2C.h>

class LCD_Display {
public:
    // Constructor
    LCD_Display(uint8_t lcdAddr, uint8_t lcdCols, uint8_t lcdRows);
    
    // Initialize the display
    void begin();
    
    // Print a message on a specific row
    void printMessage(const char* message, uint8_t row);
    
private:
   LiquidCrystal_I2C lcd;
};

#endif // LCD_DISPLAY_H
