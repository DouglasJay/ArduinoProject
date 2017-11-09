#include <Wire.h>                            // I2C control library
#include <LiquidCrystal_I2C.h>          // LCD library

LiquidCrystal_I2C lcd(0x3F,16,2);  // set the LCD address to 0x20 for a 16 chars and 2 line display

void setup()
{
  lcd.init();                      // initialize the lcd 
 
  // Print a message to the LCD.
  lcd.backlight();  // turn on backlight
  lcd.print("Hello, world!");
}

void loop()
{
}
