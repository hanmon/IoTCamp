//透過IDE中Serial Monitor，以find尋找"chtti"字串
char targetString[ ] = "chtti";
void setup() {
  //初始化序列埠
  Serial.begin(9600);
  Serial.println("A test for \"find\"");
}
void loop() {
}
void serialEvent()
{
  if (Serial.find(targetString))
  {
    Serial.print("Target string:");
    Serial.print(targetString);
    Serial.println(" found!");
  }
}
