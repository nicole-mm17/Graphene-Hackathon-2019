char dataString[50] = {0};
int a = 0;

void setup(){
Serial.begin(9600);
}

void loop(){
  a++;
  sprintf(dataString, "%02X", a);
  Serial.println(dataString);
  delay(1000);
}
