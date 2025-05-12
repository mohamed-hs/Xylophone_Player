#define STEP1_1 2
#define STEP1_2 3
#define STEP1_3 4
#define STEP1_4 5

#define STEP2_1 6
#define STEP2_2 7
#define STEP2_3 8
#define STEP2_4 9

#define SERVO_1 10
#define SERVO_2 11

#include <Servo.h>
#include <AccelStepper.h>
#include <MultiStepper.h>

// #define STEPS 2048  // number of strides to reach 360 rotation

const int bpm = 60; // Max bpm for stepper motor to function properly
const int teethPerMM = 2;

const int C_1 = 1;
const int D_1 = 2;
const int E_1 = 3;
const int F_1 = 4;
const int G_1 = 5;
const int A_1 = 6;
const int B_1 = 7;
const int C_2 = 8;
const int D_2 = -1;
const int E_2 = -2;
const int F_2 = -3;
const int G_2 = -4;
const int A_2 = -5;
const int B_2 = -6;
const int C_3 = -7;

AccelStepper stepper_1(AccelStepper::FULL4WIRE, STEP1_1, STEP1_2, STEP1_3, STEP1_4);
AccelStepper stepper_2(AccelStepper::FULL4WIRE, STEP2_1, STEP2_2, STEP2_3, STEP2_4);

MultiStepper steppers;

Servo servo1;
Servo servo2;

int pos = 0;

int previous = 0;

void setup() {
  pinMode(STEP1_1, OUTPUT);
  pinMode(STEP1_2, OUTPUT);
  pinMode(STEP1_3, OUTPUT);
  pinMode(STEP1_4, OUTPUT);

  pinMode(STEP2_1, OUTPUT);
  pinMode(STEP2_2, OUTPUT);
  pinMode(STEP2_3, OUTPUT);
  pinMode(STEP2_4, OUTPUT);

  servo1.attach(10);
  servo2.attach(11);

  stepper_1.setMaxSpeed(95 * bpm / 60);
  stepper_2.setMaxSpeed(95 * bpm / 60);

  steppers.addStepper(stepper_1);
  steppers.addStepper(stepper_2);
  
}

void loop() {
  long positions[2] = {-2048, 2000};

  steppers.moveTo(positions);
  steppers.runSpeedToPosition();
}

int goToNotes(int newNote_1, int prevNote_1, int newNote_2, int prevNote_2) {
  int distance_1 = (newNote_1 - prevNote_1) * 25;
  int distance_2 = (newNote_2 - prevNote_2) * 25;

  int position_1 = round(distance_1 * 123.5 / 64);
  int position_2 = round(distance_2 * 123.5 / 64);

  long positions[2];

  steppers.moveTo(positions);
  steppers.runSpeedToPosition();
}


void servoTest() {
  // servo1.write(90);
  for (pos = 0; pos <= 60; pos++) {
    servo1.write(pos);
    servo2.write(pos);
    delay(5);
  }
  for (pos = 60; pos >= 0; pos--) {
    // in steps of 1 degree
    servo1.write(pos);
    servo2.write(pos);
    delay(5);
  }
}