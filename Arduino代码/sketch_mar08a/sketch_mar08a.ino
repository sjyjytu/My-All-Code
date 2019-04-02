int kaiguan =7;
int cred=8;
int cyellow = 9;
int cgreen = 10;
int wred = 11;
int wgreen = 12;
void setup() 
{
        pinMode(kaiguan,INPUT);
        pinMode(cred,OUTPUT);
        pinMode(cyellow,OUTPUT);
        pinMode(cgreen,OUTPUT);
        pinMode(wred,OUTPUT);
        pinMode(wgreen,OUTPUT);
}
void loop()
{
  while(digitalRead(kaiguan)==HIGH)
    {
      digitalWrite(cyellow,HIGH);
      digitalWrite(wgreen,HIGH);
      delay(2000);
      digitalWrite(cyellow,LOW);
      digitalWrite(cred,HIGH);
      delay(8000);
    }
  digitalWrite(wred,HIGH);
  digitalWrite(wgreen,LOW);
  digitalWrite(cred,HIGH);
  delay(10000);
  digitalWrite(cyellow,HIGH);
  digitalWrite(cred,LOW);
  delay(2000);
  digitalWrite(cgreen,HIGH);
  digitalWrite(cyellow,LOW);
  delay(10000);
}
