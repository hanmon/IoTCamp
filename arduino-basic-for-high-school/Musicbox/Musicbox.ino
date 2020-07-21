/*
  MusicBox
  Play one of three songs by pushing button
  Components:
  1.Buzzer on Pin14,pin14接到Buzzer正極
  2.Push button on Pin5~7 for selecting one of three songs
  Author:Bruce Chiu
  Date: 2019-07-22
  Email:boo.chiu@gmail.com
*/
const int buzzerPin = 14; // pin14接到Buzzer正極
const int btnPins[] = {5, 6, 7};
char noteChar[] =     {'C', 'D', 'E', 'F', 'G', 'A', 'B', '1', '2', '3', '4', '5', '6', '7'}; //兩個八度音符的代號
byte noteLen = sizeof(noteChar);
//int freqMap[] = {131, 147, 165, 175, 196, 220, 247, 262, 294, 330, 349, 392, 440, 494}; //音符的代號頻率
int freqMap[] = {262, 294, 330, 349, 392, 440, 494, 523, 587, 659, 698, 784, 880, 988}; //音符的代號頻率
int songNumber = 0;
volatile int btnNumberPushed = -1;
unsigned long debounceTime = 20;
volatile unsigned long lastTriggeredTime = 0;
volatile bool lastBtnState[3] = {HIGH,HIGH,HIGH};
volatile bool lastLedState = LOW;
//char songTwoTiger[]="12311231345 345 565431565431 1G1 1G1";    //簡譜，空白代表休止符
//char tempoMap[]="222222222222222211112211112212222222";//節奏表，對應簡譜的每個音符

char song1[] = "12311231345 345 565431565431 1G1 1G1";
char song2[] = "1155665 4433221 5544332 5544332 1155665 4433221";

char tempoMap1[] = "222222222222222211112211112212222222";
char tempoMap2[] = "11111112111111121111111211111112111111121111111";

char* songs[] {
  "12311231345 345 565431565431 1G1 1G1", //第一首歌：兩隻老虎
  "1155665 4433221 5544332 5544332 1155665 4433221",//第二首歌：小星星(簡譜)，空白代表休止符
  "1113555 66615 4446333 22225 51113555 66615 4446333 22231"//第三首歌：小毛驢(簡譜)，空白代表休止符
};

char* tempoMap[] = {
  "222222222222222211112211112212222222",//第一首歌節奏
  "11111111111111111111111111111111111111111111111",//第二首歌節奏
  "11111111111121111111111111121111111111111211111111111111",//第三首歌節奏

};


void setup()
{ //無須設定pin模式
  Serial.begin(115200);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(13, OUTPUT);
  //pinMode(18, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), btn1ISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(3), btn2ISR, CHANGE);
  //attachInterrupt(digitalPinToInterrupt(18), btn3ISR, RISING);
  Serial.println("Music Box");
}

void btn1ISR() {
  //Serial.println(lastBtnState[0]?"HIGH":"LOW");
  if (millis() - lastTriggeredTime > debounceTime) {
    if (lastBtnState[0] == LOW) {
      toggleLED();
      btnNumberPushed = 0;
      Serial.println("triggered");
    }
    lastBtnState[0] ^=1;
    noTone(buzzerPin);
  }
  lastTriggeredTime = millis();
}

void btn2ISR() {
   Serial.println(lastBtnState[0]?"HIGH":"LOW");
  if (millis() - lastTriggeredTime > debounceTime) {
    if (lastBtnState[1] == LOW) {
      toggleLED();
      btnNumberPushed = 1;
    }
    lastBtnState[1] ^=1;
    noTone(buzzerPin);
  }
  lastTriggeredTime = millis();
}

void btn3ISR() {
  if (millis() - lastTriggeredTime > debounceTime) {
    if (lastBtnState[2] == LOW) {
      toggleLED();
      btnNumberPushed = 2;
    }
    lastBtnState[2] ^=1;
    noTone(buzzerPin);
  }
  lastTriggeredTime = millis();
}


void loop()
{
  if (btnNumberPushed >= 0) {
    songNumber = btnNumberPushed;
    btnNumberPushed = -1;
    int songLen = strlen(songs[songNumber]);
    int duration = 0;
    Serial.println("\nsongLen:" + String(songLen));
    for (int i = 0; i < songLen; i++)// 根據簡譜播放音樂
    {
      //將ascii轉成數值，算出duration的時間
      duration = ((int)(tempoMap[songNumber][i] - '0')) * 1000 / 8;
      //Serial.print(songs[songNumber][i]);
      Serial.println(duration);
      playNote(songs[songNumber][i], duration);
      //Serial.println(songTwoTiger[i]);
    }
    delay(1000);
  }

}

void playNote(char note, int duration)
{
  int pauseBetweenNotes = duration * 1.3;
  // 根據傳入的音符播出
  for (int i = 0; i < noteLen; i++)
  {
    // 比對簡譜的音符與音符表，找出其頻率並播放
    if (noteChar[i] == note) {
      tone(buzzerPin, freqMap[i], duration);
    }
  }
  delay(pauseBetweenNotes);
  //    noTone(buzzerPin);

}

void toggleLED(){
  lastLedState=!lastLedState;
  digitalWrite(13,lastLedState);
}
