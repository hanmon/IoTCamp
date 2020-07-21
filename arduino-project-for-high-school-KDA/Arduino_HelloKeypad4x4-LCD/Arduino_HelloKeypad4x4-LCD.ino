/* @file HelloKeypad.pde
|| @version 1.0
|| @author Alexander Brevig
|| @contact alexanderbrevig@gmail.com
||
|| @description
|| | Demonstrates the simplest use of the matrix Keypad library.
|| #
*/
#include <Keypad.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display


const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'D','C','B','A'},
  {'#','9','6','3'},
  {'0','8','5','2'},
  {'*','7','4','1'}
};
byte rowPins[ROWS] = {31, 33, 35, 37}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {39, 41, 43,45}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
int x=0,y=0;
void setup(){
  Serial.begin(9600);
  lcd.begin();
   lcd.cursor_on();
   lcd.clear();
   lcd.backlight();
}
  
void loop()
{
  char key = keypad.getKey();
  
  if (key){
    Serial.println(key);
  }
    if  (key == '#') {
     y++;x=0;
     if(y==2) { lcd.clear(); lcd.cursor_on(); lcd.setCursor(0,0);}
     lcd.cursor_on();
     lcd.setCursor(x,y);
    }
   else {
  if(key)  // Check for a valid key.
  {
       //Serial.println(key);
    if (x == 16){ 
    x=0;
    y++;    }
    if (y == 2 ) y =0;
    lcd.cursor_on();
    lcd.setCursor(x,y);
    lcd.print(key);
    x ++;
   }
 } 
}
