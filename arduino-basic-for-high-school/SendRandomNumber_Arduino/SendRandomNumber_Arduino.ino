//透過serail port送出以'S'開頭的隨機二進位資料(0~65535)
int intValue;    // an integer value (16 bits)

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  Serial.print('S'); // send a header character
  // send a random integer
  intValue = random(65535); // generate a random number between 0 and 65535
  // send the two bytes that comprise an integer
  Serial.write(lowByte(intValue));// send the low byte
  Serial.write(highByte(intValue)); // send the high byte
  delay(1000);
}
