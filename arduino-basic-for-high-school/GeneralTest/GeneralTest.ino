char* names[]={
 "boo",
  "bruce",
  "joey"
};
void setup()
{
  Serial.begin(9600);
    Serial.print("Hello World");
}

void loop()
{
  Serial.print("len");
  Serial.println(s(names[0]));
}
