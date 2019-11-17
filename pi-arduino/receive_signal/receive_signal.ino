#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(10, 9); // CE, CSN
const byte address[6] = "00001";

void setup(){
  Serial.begin(9600);
  
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();

}
int count = 0;
void loop(){
  int r = 1;
  if(Serial.available()){
    r = r*(Serial.read()-'0');
    Serial.println(r);
    
    radio.write(&r, sizeof(r));
    delay(100);
  }
}
