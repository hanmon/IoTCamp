int btnPin = 2;
int ledPin = 13;
boolean ledState = LOW;
boolean prevBtnState = LOW;
volatile boolean bounceEvalFlag=false;
volatile unsigned long startTime=0,prevTriggerTime=0,bounceDuration=0;
volatile int triggerCount=0;
char strBuffer[50];
void setup() {
  //for arduino uno
  pinMode(btnPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(btnPin),btnHandlerArduino, FALLING);
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
    Serial.println("Please press the button!");
    Serial.println();
    bounceDuration=0;
    triggerCount=0;
    prevTriggerTime=0;
    startTime=0;
    bounceEvalFlag=true;
    delay(3000);
    bounceDuration=prevTriggerTime-startTime;
    Serial.println("End of evaluation");
    sprintf(strBuffer,"Triggered %d times, and bounce duration is about %d us",triggerCount,bounceDuration);
    Serial.println(strBuffer);
    bounceEvalFlag=false;
    delay(3000);
}

//for arduino uno
void btnHandlerArduino(){
  if(bounceEvalFlag==true){  
    if(triggerCount++==0){
      startTime=micros();
    }
    prevTriggerTime=micros(); 
  }
}
