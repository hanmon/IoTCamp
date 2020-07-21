/**
 * Displays text sent over the serial port (e.g. from the Serial Monitor) on
 * an attached LCD.
 */
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
	lcd.begin();
	lcd.backlight();
  
	// Initialize the serial port at a speed of 9600 baud
	Serial.begin(9600);

  lcd.setCursor ( 0, 0 );        // go to home
  lcd.print("Hello World!");  
  lcd.setCursor ( 0, 1 );        // go to the next line
  lcd.print ("I Love Arduino!");
  delay ( 3000 );
  lcd.clear();
  lcd.setCursor( 0, 0 );
  lcd.print("Type to display");
  lcd.setCursor( 0, 1 );
  lcd.print("On SerialMonitor");
}

void loop()
{
	// If characters arrived over the serial port...
	if (Serial.available()) {
		// Wait a bit for the entire message to arrive
		delay(10);
		// Clear the screen
		lcd.clear();

		// Write all characters received with the serial port to the LCD.
		while (Serial.available() > 0) {
			lcd.write(Serial.read());
		}
	}
}
