#include <bitswap.h>
#include <chipsets.h>
#include <color.h>
#include <colorpalettes.h>
#include <colorutils.h>
#include <controller.h>
#include <cpp_compat.h>
#include <dmx.h>
#include <FastLED.h>
#include <fastled_config.h>
#include <fastled_delay.h>
#include <fastled_progmem.h>
#include <fastpin.h>
#include <fastspi.h>
#include <fastspi_bitbang.h>
#include <fastspi_dma.h>
#include <fastspi_nop.h>
#include <fastspi_ref.h>
#include <fastspi_types.h>
#include <hsv2rgb.h>
#include <led_sysdefs.h>
#include <lib8tion.h>
#include <noise.h>
#include <pixelset.h>
#include <pixeltypes.h>
#include <platforms.h>
#include <power_mgt.h>

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


#define LED_PIN     3
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB

CRGB right_front[14];
CRGB right_back[14];
CRGB left_front[14];
CRGB left_back[14];

RF24 radio(8, 10); // CE, CSN
const byte address[6] = "00001";
void setup() {
  delay(1000);
  FastLED.addLeds<LED_TYPE, 3, COLOR_ORDER>(right_front, 14);
  FastLED.addLeds<LED_TYPE, 4, COLOR_ORDER>(right_back, 14);
  FastLED.addLeds<LED_TYPE, 5, COLOR_ORDER>(left_front, 14);
  FastLED.addLeds<LED_TYPE, 6, COLOR_ORDER>(left_back, 14);
  
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();
}
int state = 0;
void loop() {
  if (radio.available()) {
    int input;
    radio.read(&input, sizeof(input));
    Serial.println(input);
    if (input == 1){
      if (state==1){state=0;} // the light will return to 0 state after signal being sent twice 
      else{state=1;}
      }
    if (input == 2){
      if (state==2){state=0;}
      else{state=2;}
    }
    if (input == 3){
      state=0;
    }
    if (input == 52){
      state=0;
    }


           

      delay(10);
      }
   if (state==0){
    FastLED.clear();
    for (int i = 0; i < 14 -1; i++) {
      left_front[i].setRGB(255,0,0);
      left_back[i].setRGB(255,0,0);
      right_front[i].setRGB(255,0,0);
      right_back[i].setRGB(255,0,0);
      FastLED.show();
      delay(15);
      }
   }
   
   if(state==1){
    FastLED.clear();
    for (int i = 0; i < 14 -1; i++) {
      right_back[i].setRGB(255,60,0);
      left_front[i].setRGB(255,60,0);
     FastLED.show();
      delay(15);
      }
   }

    if(state==2){
    FastLED.clear();
    for (int i = 0; i < 14 - 1; i++) {
      right_front[i].setRGB(255,60,0);
      left_back[i].setRGB(255,60,0);
      FastLED.show();
      delay(15);
      }
    }

    else{
    FastLED.clear();
    for (int i = 0; i < 14 - 1; i++) {
      right_front[i].setRGB(255,0,0);
      right_back[i].setRGB(255,0,0);
      FastLED.show();
      delay(15);
      }
      
    }
   
}
