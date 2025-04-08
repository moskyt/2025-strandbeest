#include <Adafruit_NeoPixel.h> 

Adafruit_NeoPixel LED1 = Adafruit_NeoPixel(1,2,NEO_GRB + NEO_KHZ400);
Adafruit_NeoPixel LED2 = Adafruit_NeoPixel(1,9,NEO_GRB + NEO_KHZ400);

void setup() {
  Serial.begin(9600);
  delay(1000);

  LED1.begin();
  LED1.setBrightness(brightness);
  LED2.begin();
  LED2.setBrightness(brightness);

  LED1.setPixelColor(0, 255,255,255);
  LED2.setPixelColor(0, 255,255,255);
  
  LED1.show(); 
  LED2.show(); 

}

void loop() {
  delay(100);
}
