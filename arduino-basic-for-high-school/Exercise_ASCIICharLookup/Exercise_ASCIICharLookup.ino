//To lookup any ascii character and show its DEC,HEX,OCT,BIN value
void setup()
{
  Serial.begin(115200);
}

void loop()
{
  byte incommingByte=0;
  Serial.print("Please enter an ASCII character:");
  while(Serial.available()==0);
  incommingByte=Serial.read();
  Serial.write(incommingByte);
  Serial.print("\nDEC:"+String(incommingByte,DEC)+"\t");
  Serial.print("HEX:"+String(incommingByte,HEX)+"\t");
  Serial.print("OCT:"+String(incommingByte,OCT)+"\t");
  Serial.println("BIN:"+String(incommingByte,BIN)+"\t");
}
