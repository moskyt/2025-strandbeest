#include <AFMotor.h>
#include <Adafruit_NeoPixel.h> 

AF_DCMotor motor1(3, MOTOR34_64KHZ); // create motor #3, 64KHz pwm
AF_DCMotor motor2(4, MOTOR34_64KHZ); // create motor #4, 64KHz pwm

Adafruit_NeoPixel LED = Adafruit_NeoPixel(2,2,NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Motor test!");
  
  LED.begin();
  LED.setBrightness(255);
  LED.setPixelColor(0, 255, 0, 0);
  LED.setPixelColor(1, 0, 0, 255);
  LED.show(); 

  motor1.setSpeed(200);     // set the speed to 200/255
  motor2.setSpeed(200);     // set the speed to 200/255
}

void loop() {
  Serial.print("tick1");
  LED.setPixelColor(0, 255, 0, 0);
  LED.setPixelColor(1, 0, 0, 255);
  LED.show(); 

  motor1.run(FORWARD);      // turn it on going forward
  delay(1000);

  Serial.print("tock1");
  motor1.run(BACKWARD);     // the other way
  delay(1000);
  
  Serial.print("tack1");
  motor1.run(RELEASE);      // stopped
  delay(1000);

  Serial.print("tick2");
  LED.setPixelColor(1, 255, 0, 0);
  LED.setPixelColor(0, 0, 0, 255);
  LED.show(); 

  motor2.run(FORWARD);      // turn it on going forward
  delay(1000);

  Serial.print("tock2");
  motor2.run(BACKWARD);     // the other way
  delay(1000);
  
  Serial.print("tack2");
  motor2.run(RELEASE);      // stopped
  delay(1000);
}