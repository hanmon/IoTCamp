/*
  BuzzerWithTempo
  演奏兩隻老虎曲目，有節奏，循環播放
  pin2接到Buzzer正極
 */
const int buzzerPin = 8; // pin2接到Buzzer正極
int duration = 125;  // 每個音符的時間長度
char noteChar[] =     {'C','D','E','F','G','A','B','1','2','3','4','5','6','7'}; //兩個八度音符的代號
byte noteLen=sizeof(noteChar);
int freqMap[] = {131,147,165,175,196,220,247,262,294,330,349,392,440,494};//音符的代號頻率
char songTwoTiger[]="12311231345 345 565431565431 1G1 1G1";    //簡譜，空白代表休止符
byte songLen=sizeof(songTwoTiger)-1;
char tempoMap[]="222222222222222211112211112212222222";//節奏表，對應簡譜的每個音符
void setup()
{//無須設定pin模式 
  //Serial.begin(9600);
}
void loop()
{
  for (int i = 0; i < songLen; i++)// 根據簡譜播放音樂
  {
    //將ascii轉成數值，算出duration的時間
    duration=((int)(tempoMap[i]-'0'))*125;
    playNote(songTwoTiger[i], duration);
    //Serial.println(songTwoTiger[i]);
  }
  delay(5000); // 與下次播放的時間間隔為5秒
}

void playNote(char note, int duration)
{
  // 根據傳入的音符播出
  for (int i = 0; i < noteLen; i++)
  {
    // 比對簡譜的音符與音符表，找出其頻率並播放
    if (noteChar[i] == note) 
      tone(buzzerPin, freqMap[i], duration); 
  }
  // 若無符合的，則靜默，作為休止音
  delay(duration);
}
