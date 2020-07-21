/*
  MusicBox
  Play one of three songs by pushing button
  Components:
  1.Buzzer on Pin3,pin3接到Buzzer正極
  2.Push button on Pin4~11 for selecting one of three songs
  Author:Bruce Chiu
  Date: 2019-07-22
  Email:boo.chiu@gmail.com
*/
const int buzzerPin = 3; // pin3接到Buzzer正極
char noteChar[] =     {'C', 'D', 'E', 'F', 'G', 'A', 'B', '1', '2', '3', '4', '5', '6', '7'}; //兩個八度音符的代號
byte noteLen = sizeof(noteChar);
//int freqMap[] = {131, 147, 165, 175, 196, 220, 247, 262, 294, 330, 349, 392, 440, 494}; //音符的代號頻率
int freqMap[] = {262, 294, 330, 349, 392, 440, 494, 523, 587, 659, 698, 784, 880, 988}; //音符的代號頻率
int songNumber = 0;
int btnNumberPressed = 0;
unsigned long debounceTime = 20;

char* songs[] {
  "12311231345 345 565431565431 1G1 1G1", //第一首歌：兩隻老虎
  "1155665 4433221 5544332 5544332 1155665 4433221",//第二首歌：小星星(簡譜)，空白代表休止符
  "1113555 66615 4446333 22225 51113555 66615 4446333 22231",//第三首歌：小毛驢(簡譜)，空白代表休止符
  "11123 33345 56543 55231",//第四首歌：哈巴狗
  "5552332 77665 555 555 5555555 5552332 77665",//第五首歌：
  "333 333 35123 4444433 322325 333 333 35123 4444433 55421",//第六首歌：聖誕鈴聲
  "444444444444444444444444444444444444",//第七首歌：
  "444444444444444444444444444444444444"//第八首歌：
};

char* tempoMap[] = {
  "222222222222222211112211112212222222",//第一首歌節奏
  "11111111111111111111111111111111111111111111111",//第二首歌節奏
  "11111111111121111111111111121111111111111211111111111111",//第三首歌節奏
  "11111111111111111111111",//第四首歌節奏
  //"5552332 77665 555 555 5555555 5552332 77665",//第五首歌節奏
  "1111111111111111111111111111111111111111111",//第五首歌節奏
  //"333 333 35123 4444433 322325 333 333 35123 4444433 55421",//第六首歌：
  "11111111111111111111111111111111111111111111111111111111",//第六首歌節奏
  "111111111111111111111111111111111111",//第七首歌節奏
  "111111111111111111111111111111111111"//第八首歌節奏
};


void setup()
{ 
  initBtnPins();
  Serial.begin(115200);
  Serial.println("Arduino Music Box, Please select your favorite song.");
}

void loop()
{
  btnNumberPressed=showBtnPressed();
  if (btnNumberPressed != 0) {
    songNumber = btnNumberPressed-4;
    int songLen = strlen(songs[songNumber]);
    int duration = 0;
    Serial.println("\nsongNumber:" + String(songNumber));
    Serial.println("\nsongLen:" + String(songLen));
    Serial.println(songs[songNumber]);
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
