//Arduino Piano
/*

Visit the Channel for more interesting projects

https://www.youtube.com/channel/UCks-9JSnVb22dlqtMgPjrlg

*/

#define T_C 262
#define T_D 294
#define T_E 330
#define T_F 349
#define T_G 392
#define T_A 440
#define T_B 493

const int C = 9;
const int D = 8;
const int E = 7;
const int F = 6;
const int G = 5;
const int A = 4;
const int B = 3;

const int buzzerPin = 14;
const int ledPin = 12;

void setup()
{
  pinMode(ledPin, OUTPUT);
  pinMode(C, INPUT);
  digitalWrite(C,HIGH);
  
  pinMode(D, INPUT);
  digitalWrite(D,HIGH);
  
  pinMode(E, INPUT);
  digitalWrite(E,HIGH);
  
  pinMode(F, INPUT);
  digitalWrite(F,HIGH);
  
  pinMode(G, INPUT);
  digitalWrite(G,HIGH);
  
  pinMode(A, INPUT);
  digitalWrite(A,HIGH);
  
  pinMode(B, INPUT);
  digitalWrite(B,HIGH);

   digitalWrite(ledPin,LOW);
}

void loop()
{
  while(digitalRead(C) == LOW)
  {
    tone(buzzerPin,T_C);
    digitalWrite(ledPin,HIGH);
  }

  while(digitalRead(D) == LOW)
  {
    tone(buzzerPin,T_D);
    digitalWrite(ledPin,HIGH);
  }

  while(digitalRead(E) == LOW)
  {
    tone(buzzerPin,T_E);
    digitalWrite(ledPin,HIGH);
  }

  while(digitalRead(F) == LOW)
  {
    tone(buzzerPin,T_F);
    digitalWrite(ledPin,HIGH);
  }

  while(digitalRead(G) == LOW)
  {
    tone(buzzerPin,T_G);
    digitalWrite(ledPin,HIGH);
  }

  while(digitalRead(A) == LOW)
  {
    tone(buzzerPin,T_A);
    digitalWrite(ledPin,HIGH);
  }

  while(digitalRead(B) == LOW)
  {
    tone(buzzerPin,T_B);
    digitalWrite(ledPin,HIGH);
  }

  noTone(buzzerPin);
  digitalWrite(ledPin,LOW);

}
