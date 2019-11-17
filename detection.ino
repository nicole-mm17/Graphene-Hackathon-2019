int trigPin = 8;    
int echoPin=9;
long duration, cm;
int led=10; //can modify later
int brightness;

void setup() {
  //Serial Port begin
  Serial.begin (9600);
  //Define inputs and outputs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led,OUTPUT);
  
  
}
 
void loop() {
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
 
  
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
 
  cm = (duration/2) / 29.1;
  if (cm<150){
  digitalWrite(led, HIGH);
  delay(cm*10);
  digitalWrite(led, LOW);
  delay(cm*10);}
  else {
    digitalWrite(led,LOW);
  }
  
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  delay(250);
  
  
}
