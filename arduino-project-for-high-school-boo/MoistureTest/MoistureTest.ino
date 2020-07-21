/*
  # Example code for the moisture sensor
  # Connect the sensor to the A0(Analog 0) pin on the Arduino board
  # the sensor value description
  # 0  ~300     dry soil
  # 300~700     humid soil
  # 700~950     in water

*/
unsigned long lastTime = 0;
void setup() {
  Serial.begin(115200);
}
void loop() {
  if (millis() - lastTime>1000) {
    Serial.print("Moisture Sensor Value:");
    Serial.println(analogRead(0));
    lastTime=millis();
  }
}
