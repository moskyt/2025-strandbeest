#define DECODE_NEC

// IR pins
#define IR_RECEIVE_PIN   2
#include <IRremote.hpp>

// motor shield pins
#define PIN_BUZZER 4
#define PIN_E1     10
#define PIN_M1     12
#define PIN_E2     11
#define PIN_M2     13

// commands
#define CMD_FWD    0x18
#define CMD_LEFT   0x08
#define CMD_RIGHT  0x5A
#define CMD_BACK   0x52
#define CMD_STOP   0x1C
#define CMD_BEEP   0x0D

enum mode {FWD, BACK, LEFT, RIGHT, STOP, FWD_LEFT, FWD_RIGHT};
mode robot_mode = STOP;
int run_counter = 0;
int turn_rate = 0;
const int max_counter = 100;
const int speed = 250, dspeed = 50;

void setup() {

  Serial.begin(9600);
  delay(1000);

  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_M1, OUTPUT);
  pinMode(PIN_M2, OUTPUT);
  pinMode(PIN_E1, OUTPUT);
  pinMode(PIN_E2, OUTPUT);

  IrReceiver.begin(IR_RECEIVE_PIN);

  Serial.println("HELO");
}

void loop() {
  if (IrReceiver.decode()) {
    Serial.print(F("New command received: "));
    Serial.println(IrReceiver.decodedIRData.command);
    if (IrReceiver.decodedIRData.command == CMD_FWD) {
      robot_mode = FWD;
      run_counter = max_counter;
    } else 
    if (IrReceiver.decodedIRData.command == CMD_BACK) {
      Serial.println(F("Go :: BACK"));
      robot_mode = BACK;
      run_counter = max_counter;
    } else 

    if (IrReceiver.decodedIRData.command == CMD_LEFT) {
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
    if (IrReceiver.decodedIRData.command == CMD_BEEP) {
      Serial.println("Beep.");
      tone(PIN_BUZZER, 1000); 
      delay(100); 
      noTone(PIN_BUZZER);           
    };
    IrReceiver.resume();
  }
  if (run_counter > 0) {
    run_counter--;
    if (run_counter <= 0) robot_mode = STOP;
  }
  if (robot_mode == STOP) {
      digitalWrite(PIN_M1, HIGH);
      digitalWrite(PIN_M2, HIGH);
      analogWrite(PIN_E1, 0);
      analogWrite(PIN_E2, 0);
  } else 
  if (robot_mode == FWD) {
      digitalWrite(PIN_M1, LOW);
      digitalWrite(PIN_M2, HIGH);
      analogWrite(PIN_E1, speed);
      analogWrite(PIN_E2, speed);
  } else 
  if (robot_mode == FWD_LEFT) {
      digitalWrite(PIN_M1, LOW);
      digitalWrite(PIN_M2, HIGH);
      analogWrite(PIN_E1, speed - dspeed*turn_rate);
      analogWrite(PIN_E2, speed);
  } else 
  if (robot_mode == FWD_RIGHT) {
      digitalWrite(PIN_M1, LOW);
      digitalWrite(PIN_M2, HIGH);
      analogWrite(PIN_E1, speed);
      analogWrite(PIN_E2, speed - dspeed*turn_rate);
  } else 
  if (robot_mode == BACK) {
      // actually goes:  back
      digitalWrite(PIN_M1, HIGH);
      digitalWrite(PIN_M2, LOW);
      analogWrite(PIN_E1, speed);
      analogWrite(PIN_E2, speed);
  } else 
  if (robot_mode == LEFT) {
      // actually goes:  left
      digitalWrite(PIN_M1, HIGH);
      digitalWrite(PIN_M2, HIGH);
      analogWrite(PIN_E1, speed);
      analogWrite(PIN_E2, speed);
  } else 
  if (robot_mode == RIGHT) {
      // actually goes: right
      digitalWrite(PIN_M1, LOW);
      digitalWrite(PIN_M2, LOW);
      analogWrite(PIN_E1, speed);
      analogWrite(PIN_E2, speed);
  };  
  delay(50);
}
