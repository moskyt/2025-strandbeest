#include <AFMotor.h>
#include <Adafruit_NeoPixel.h> 

// motors
AF_DCMotor motor1(3, MOTOR34_64KHZ); // create motor #3, 64KHz pwm
AF_DCMotor motor2(4, MOTOR34_64KHZ); // create motor #4, 64KHz pwm

// lights
Adafruit_NeoPixel LED = Adafruit_NeoPixel(4,2,NEO_GRB + NEO_KHZ800);

// IR pins
#define DECODE_NEC
#define IR_RECEIVE_PIN   10
#include <IRremote.hpp>

// commands
#define CMD_FWD    24
#define CMD_LEFT    8
#define CMD_RIGHT  90
#define CMD_BACK   82
#define CMD_STOP   28

#define CMD_LIGHTS_OFF 13  //#
#define CMD_LIGHTS_ON  22  //*

#define CMD_LIGHTS_DARKER   69  //1
#define CMD_LIGHTS_NORMAL   70  //2
#define CMD_LIGHTS_BRIGHTER 71  //3
#define CMD_LIGHTS_PURPLE   68  //4
#define CMD_LIGHTS_ORANGE   64  //5
#define CMD_LIGHTS_STANDARD 67  //6 

enum mode {FWD, BACK, LEFT, RIGHT, STOP, FWD_LEFT, FWD_RIGHT};
mode robot_mode = STOP;
int run_counter = 0;
int turn_rate = 0;
const int max_counter = 100;
const int speed = 250, dspeed = 50;
const int std_brightness = 100;
int brightness = std_brightness;

int color_front[3] = {255, 255, 255};
int color_back[3]  = {255, 0,   0};

void update_light_colors() {
  LED.setPixelColor(0, color_front[0], color_front[1], color_front[2]);
  LED.setPixelColor(1, color_back[0],  color_back[1],  color_back[2]);
  LED.setPixelColor(2, color_front[0< ], color_front[1], color_front[2]);
  LED.setPixelColor(3, color_back[0],  color_back[1],  color_back[2]);
  LED.show(); 
}

void setup() {

  Serial.begin(9600);
  delay(1000);

  LED.begin();
  LED.setBrightness(brightness);
  update_light_colors();

  IrReceiver.begin(IR_RECEIVE_PIN);

  Serial.println("HELO");
}

void loop() {
  if (IrReceiver.decode()) {
    Serial.print(F("New command received: "));
    Serial.println(IrReceiver.decodedIRData.command);
    if (IrReceiver.decodedIRData.command == CMD_FWD) {
      Serial.println(F("Go :: FORWARD"));
      robot_mode = FWD;
      run_counter = max_counter;
    } else 
    if (IrReceiver.decodedIRData.command == CMD_BACK) {
      Serial.println(F("Go :: BACK"));
      robot_mode = BACK;
      run_counter = max_counter;
    } else 
    if (IrReceiver.decodedIRData.command == CMD_LEFT) {
      Serial.println(F("Go :: LEFT"));
      if (robot_mode == FWD) {
        robot_mode = FWD_LEFT;
        turn_rate = 1;
      } else
      if (robot_mode == FWD_LEFT) {
        if (turn_rate < 3) turn_rate++;
      } else 
        robot_mode = LEFT;
  
      run_counter = max_counter;
    } else
    if (IrReceiver.decodedIRData.command == CMD_RIGHT) {
      Serial.println(F("Go :: RIGHT"));
      if (robot_mode == FWD) {
        robot_mode = FWD_RIGHT;
        turn_rate = 1;
      } else
      if (robot_mode == FWD_RIGHT) {
        if (turn_rate < 3) turn_rate++;
      } else 
        robot_mode = RIGHT;

      run_counter = max_counter;
    } else 
    if (IrReceiver.decodedIRData.command == CMD_STOP) {
      Serial.println(F("Go :: STOP"));
      robot_mode = STOP;
    } else 
    if (IrReceiver.decodedIRData.command == CMD_LIGHTS_DARKER) {
      Serial.println("Lights :: brighter");
      brightness -= 10;
      if (brightness < 10) brightness = 10;
      LED.setBrightness(brightness);
      LED.show();           
    } else
    if (IrReceiver.decodedIRData.command == CMD_LIGHTS_NORMAL) {
      Serial.println("Lights :: brighter");
      brightness = std_brightness;
      LED.setBrightness(brightness);
      LED.show();           
    } else
    if (IrReceiver.decodedIRData.command == CMD_LIGHTS_BRIGHTER) {
      Serial.println("Lights :: brighter");
      brightness += 10;
      if (brightness > 255) brightness = 255;
      LED.setBrightness(brightness);
      LED.show();           
    } else
    if (IrReceiver.decodedIRData.command == CMD_LIGHTS_PURPLE) {
      Serial.println("Lights purple.");
      color_front[0] = 255; color_front[1] =   0; color_front[2] = 255; 
      color_back [0] =   0; color_back [1] =   0; color_back [2] = 255; 
      update_light_colors();
    } else
    if (IrReceiver.decodedIRData.command == CMD_LIGHTS_ORANGE) {
      Serial.println("Lights purple.");
      color_front[0] = 255; color_front[1] = 128; color_front[2] =   0; 
      color_back [0] =   0; color_back [1] = 255; color_back [2] =   0; 
      update_light_colors();
    } else
    if (IrReceiver.decodedIRData.command == CMD_LIGHTS_STANDARD) {
      Serial.println("Lights purple.");
      color_front[0] = 255; color_front[1] = 255; color_front[2] = 255; 
      color_back [0] = 255; color_back [1] =   0; color_back [2] =   0; 
      update_light_colors();
    } else
    if (IrReceiver.decodedIRData.command == CMD_LIGHTS_OFF) {
      Serial.println("Lights off.");
      LED.setBrightness(0);
      LED.show();           
    } else
    if (IrReceiver.decodedIRData.command == CMD_LIGHTS_ON) {
      Serial.println("Lights on.");
      LED.setBrightness(brightness);
      update_light_colors();
    };
    IrReceiver.resume();
  }
  if (run_counter > 0) {
    run_counter--;
    if (run_counter <= 0) robot_mode = STOP;
  }
  if (robot_mode == STOP) {
      motor1.run(RELEASE);
      motor2.run(RELEASE);
      motor1.setSpeed(0);
      motor2.setSpeed(0);
  } else 
  if (robot_mode == FWD) {
      motor1.run(FORWARD);
      motor2.run(FORWARD);
      motor1.setSpeed(speed);
      motor2.setSpeed(speed);
  } else 
  if (robot_mode == FWD_LEFT) {
      motor1.run(FORWARD);
      motor2.run(FORWARD);
      motor1.setSpeed(speed - dspeed*turn_rate);
      motor2.setSpeed(speed);
  } else 
  if (robot_mode == FWD_RIGHT) {
      motor1.run(FORWARD);
      motor2.run(FORWARD);
      motor1.setSpeed(speed);
      motor2.setSpeed(speed - dspeed*turn_rate);
  } else 
  if (robot_mode == BACK) {
      motor1.run(BACKWARD);
      motor2.run(BACKWARD);
      motor1.setSpeed(speed);
      motor2.setSpeed(speed);
  } else 
  if (robot_mode == LEFT) {
      motor1.run(FORWARD);
      motor2.run(BACKWARD);
      motor1.setSpeed(speed);
      motor2.setSpeed(speed);
  } else 
  if (robot_mode == RIGHT) {
      motor1.run(BACKWARD);
      motor2.run(FORWARD);
      motor1.setSpeed(speed);
      motor2.setSpeed(speed);
  };  
  delay(50);
}
