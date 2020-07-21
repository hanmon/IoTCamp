//利用randomSeed()函式產生亂數種子，並以讀取空接的A0腳位，使ramdom()產生的亂數序列每次不相同
const int analogPin=0;
void setup()
{
  Serial.begin(115200);
}

void loop()
{
  int randValue=0;
  randomSeed(analogRead(analogPin));
  randValue=random(0,100);
  Serial.print("Random Value:");
  Serial.println(randValue);
  delay(1000);
}