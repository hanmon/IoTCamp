//
// Using one 74HC595 to control a common-anode seven-segment display
//
//使用第D2,D3,D4腳與74HC595連接
const int bit_clock_pin = 4;
// pin 3 of 74HC595 (STCP) 
const int digit_clock_pin = 3;
// pin 2 of 74HC595 (DS) 資料
const int data_pin = 2;
// digit pattern for a 7-segment display

const byte digit_pattern[16] =

{ //DpGFEDCBA
  B00111111,  // 0
  B00000110,  // 1
  B01011011,  // 2
  B01001111,  // 3
  B01100110,  // 4
  B01101101,  // 5
  B01111101,  // 6
  B00000111,  // 7
  B01111111,  // 8
  B01101111,  // 9
  B01110111,  // A
  B01111100,  // b
  B00111001,  // C
  B01011110,  // d
  B01111001,  // E
  B01110001   // F
};
unsigned int counter = 0;
void setup()
{
  pinMode(data_pin, OUTPUT);
  pinMode(bit_clock_pin, OUTPUT);
  pinMode(digit_clock_pin, OUTPUT);  
}

void update_one_digit(int data)
{
  int i;
  byte pattern;
  // get the digit pattern to be updated
  pattern = digit_pattern[data];
  // turn off the output of 74HC595
  digitalWrite(digit_clock_pin, LOW);
  // update data pattern to be outputed from 74HC595
  // because it's a common anode LED, the pattern needs to be inverted
  shiftOut(data_pin, bit_clock_pin, MSBFIRST, ~pattern);
  // turn on the output of 74HC595
  digitalWrite(digit_clock_pin, HIGH);
}

void loop()
{ 
  int i;
  unsigned int digit_base;
  counter++;
  digit_base = 16;
  // get the value to be displayed and update one digit
  update_one_digit(counter % digit_base);
  delay(500);
}
