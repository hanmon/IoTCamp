#include <SPI.h>
#include <avr/pgmspace.h>

const byte NOOP = 0x0;
const byte DECODEMODE = 0x9;
const byte INTENSITY = 0xA;
const byte SCANLIMIT = 0xB;
const byte SHUTDOWN = 0xC;
const byte DISPLAYTEST = 0xF;
//const byte BigHeart[] = {B01100110,B11111111,B11111111,B11111111,B11111111,B01111110,B00111100,B00011000};
//const byte SmallHeart[] = {B00000000,B00100100,B01111110,B01111110,B01111110,B00111100,B00011000,B00000000};
//const byte Circle[]={B00111100,B01000010,B10000001,B10000001,B10000001,B10000001,B01000010,B00111100};
//const byte Cross[]={B10000001,B01000010,B00100100,B00011000,B00011000,B00100100,B01000010,B10000001};
const byte Patterns[][8] PROGMEM = {
  {B01100110, B11111111, B11111111, B11111111, B11111111, B01111110, B00111100, B00011000}, //0.BigHeart
  {B00000000, B00100100, B01111110, B01111110, B01111110, B00111100, B00011000, B00000000}, //1.SmallHeart
  {B00111100, B01000010, B10000001, B10000001, B10000001, B10000001, B01000010, B00111100}, //2.Circle
  {B10000001, B01000010, B00100100, B00011000, B00011000, B00100100, B01000010, B10000001}, //3.Cross
  {B00111100, B01000010, B01011010, B01000010, B10111101, B11011011, B01111110, B00111100}, //4.Flower
  {B00001000, B00001100, B00001110, B11111111, B11111111, B00001110, B00001100, B00001000}, //5.Arrow Right
  {B00010000, B00110000, B01110000, B11111111, B11111111, B01110000, B00110000, B00010000}, //6.Arrow Left
  {B00000000, B00100100, B00100100, B00000000, B10000001, B10000001, B01000010, B00111100}, //7.smile
  {B00000000, B00100100, B00100100, B00000000, B00000000, B00111100, B01000010, B00000000} //8.sad
};


int wait = 1000;
void sendSPIData(const byte reg, byte data) {
  digitalWrite(SS, LOW);
  SPI.transfer(reg);
  SPI.transfer(data);
  digitalWrite(SS, HIGH);
}

void initMAX7219() {
  pinMode(SS, OUTPUT);
  digitalWrite(SS, HIGH);
  SPI.begin();
  sendSPIData(SCANLIMIT, 7);
  sendSPIData(DECODEMODE, 0);
  sendSPIData(INTENSITY, 8);
  sendSPIData(DISPLAYTEST, 0);
  sendSPIData(SHUTDOWN, 1);
  //clear matrix
  for (int i = 1; i <= 8; i++) {
    sendSPIData(i, 0);
  }
}


void setup() {
  // put your setup code here, to run once:
  initMAX7219();
}

void loop() {
  // put your main code here, to run repeatedly:
  byte buf[8];
  for (int i = 0; i < 8; i++) {
    buf[i] = pgm_read_byte(&Patterns[7][i]);
  }
  showGraph(buf);
  delay(wait);
  for (int i = 0; i < 8; i++) {
    buf[i] = pgm_read_byte(&Patterns[8][i]);
  }
  showGraph(buf);
  delay(wait);
}

void showGraph(const byte array[]) {
  byte* ptr = array;
  for (int i = 0; i < 8; i++) {
    sendSPIData(i + 1, *(ptr + i));
  }
}
