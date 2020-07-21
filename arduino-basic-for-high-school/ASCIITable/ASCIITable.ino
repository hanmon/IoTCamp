/*　　　印出所有可見的ASCII字元及其10進位、16進位、8進位、2進位數值
 */
void setup() { 
  //Initialize serial and wait for port to open:
  Serial.begin(115200); 
  Serial.println("ASCII Table ~ Character Map"); 
} 
// 可見的ASCII字元範圍從33('!')~126('~'):
int asciiChar= 33; 
boolean printFlag=true;
void loop() {
  if(printFlag)
  {
    Serial.write(asciiChar); 
    Serial.print(", dec: "); 
    Serial.print(asciiChar);     //印出10進位數值　
    Serial.print(", hex: "); 
    Serial.print("0x");
    Serial.print(asciiChar, HEX);     //印出16進位數值
    Serial.print(", oct: ");
    Serial.print("0"); 
    Serial.print(asciiChar, OCT);     //印出8進位數值
    Serial.print(", bin: "); 
    Serial.println(asciiChar, BIN);
    asciiChar++;  //繼續下一個字元
  }
  if(asciiChar == 127) {  //　　印到126即停止
    printFlag=false;
  }

} 
