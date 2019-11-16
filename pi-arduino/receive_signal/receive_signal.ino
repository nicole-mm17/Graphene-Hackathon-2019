
void setup(){
  Serial.begin(9600);
}
int count = 0;
void loop(){
  int r = 1;
  // int test = 1;
  if(Serial.available()){
    r = r*(Serial.read()-'0');
    // test = (Serial.read()-'0');
    // count++;
    Serial.println(r);
    // Serial.println(test);
  }
}
