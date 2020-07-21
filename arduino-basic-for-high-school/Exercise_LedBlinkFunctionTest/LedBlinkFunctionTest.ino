int ledPin= 9;
// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(ledPin, OUTPUT);   
  blinkLed(ledPin,250,3); //快閃三次表示程式開始  
}

// the loop routine runs over and over again forever:
void loop() {
  blinkLed(ledPin,1000,1); //慢閃表在loop中
}

void blinkLed(int pin, int duration, int count)
{	
	while(count>0)
	{
		digitalWrite(pin,HIGH);
		delay(duration);
		digitalWrite(pin,LOW);
		delay(duration);
		count--;
	}
}
