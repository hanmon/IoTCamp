#define LEDR 8  // 設定 RGB Red-Pin
#define LEDG 9  // 設定 RGB Green-Pin
#define LEDB 10  // 設定 RGB Blue-Pin

void setup() {                
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);
}

int r = 0;
int g = 0;
int b = 0;
void loop() {
  r = random(0, 255);
  g = random(0, 255);
  b = random(0, 255);
  analogWrite(LEDR, r);
  analogWrite(LEDG, g);
  analogWrite(LEDB, b);
  delay(1000);
}
