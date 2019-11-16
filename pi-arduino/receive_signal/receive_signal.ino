
void setup(){
  Serial.begin(9600);
}
int count = 0;
void loop(){
  int r = 1;
  if(Serial.available()){
    r = r*(Serial.read()-'0');
    Serial.println(r);
  }
}
