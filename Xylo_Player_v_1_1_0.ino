// The code for our amazing GXBF


// Defining the pins for our first driver
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

#define RAIL_1 A0
#define RAIL_2 A1

#include <Servo.h>
#include <AccelStepper.h>
#include <MultiStepper.h>

// #define STEPS 2048  // number of strides to reach 360 rotation

void goToNotes(int newNote_1, int newNote_2);

long positions[2];


const int bpm = 60;  // Max bpm for stepper motor to function properly
const int teethPerMM = 2;

const int s_1 = 410;  // Steps from note to note
const int s_2 = 410;  // Steps from

const int C_1 = 0 * s_1;
const int D_1 = 1 * s_1;
const int E_1 = 2 * s_1;
const int F_1 = 3 * s_1;
const int G_1 = 4 * s_1;
const int A_1 = 5 * s_1;
const int B_1 = 6 * s_1;
const int C_2 = 7 * s_1;
const int D_2 = 6 * s_2;
const int E_2 = 5 * s_2;
const int F_2 = 4 * s_2;
const int G_2 = 3 * s_2;
const int A_2 = 2 * s_2;
const int B_2 = 1 * s_2;
const int C_3 = 0 * s_2;

int current_pos_1 = 0;
int current_pos_2 = 0;

AccelStepper stepper_1(AccelStepper::FULL4WIRE, STEP1_1, STEP1_2, STEP1_3, STEP1_4);
AccelStepper stepper_2(AccelStepper::FULL4WIRE, STEP2_1, STEP2_2, STEP2_3, STEP2_4);

MultiStepper steppers;

Servo servo1;
Servo servo2;

int servo_pos = 0;

int t = 0;

int prevNote_1 = 0;
int prevNote_2 = 0;

long unsigned t_before = 0;
long unsigned t_after = 0;
float dt = 0;

int duration = 0;
void setup() {

  Serial.begin(9600);
  pinMode(STEP1_1, OUTPUT);
  pinMode(STEP1_2, OUTPUT);
  pinMode(STEP1_3, OUTPUT);
  pinMode(STEP1_4, OUTPUT);

  pinMode(STEP2_1, OUTPUT);
  pinMode(STEP2_2, OUTPUT);
  pinMode(STEP2_3, OUTPUT);
  pinMode(STEP2_4, OUTPUT);

  pinMode(RAIL_1, INPUT);
  pinMode(RAIL_2, INPUT);

  servo1.attach(10);
  servo2.attach(11);

  stepper_1.setMaxSpeed(700 /*95 * bpm / 60*/);  // 135 is best fit speed
  stepper_2.setMaxSpeed(700 /*95 * bpm / 60*/);  // Maxx : 700

  steppers.addStepper(stepper_1);
  steppers.addStepper(stepper_2);
  servo1.write(servo_pos);
  servo2.write(servo_pos);

  int i = 1;
  while (!digitalRead(RAIL_1) || !digitalRead(RAIL_2)) {
    if (digitalRead(RAIL_1)) {
      positions[1] = -50 * i;
    } else if (digitalRead(RAIL_2)) {
      positions[0] = -50 * i;
    } else {
      positions[0] = -50 * i;
      positions[1] = -50 * i;
    }
    steppers.moveTo(positions);
    i++;
    steppers.runSpeedToPosition();
  }

  current_pos_1 = 0;
  current_pos_2 = 0;

  // Serial.println(stepper_1.currentPosition());
  // Serial.println(stepper_2.currentPosition());
  stepper_1.setCurrentPosition(current_pos_1);
  stepper_2.setCurrentPosition(current_pos_2);
  // Serial.println(stepper_1.currentPosition());
  // Serial.println(stepper_2.currentPosition());
  delay(1000);

  // t_before = millis();
  // positions[0] = C_2; // Steps of 385
  // positions[1] = D_2; // Steps of 470

  // steppers.moveTo(positions);
  // steppers.runSpeedToPosition();

  // // servoTest();
  // t_after = millis();
  // dt = (t_after - t_before) / 1000;
  // Serial.println(dt);
}

void loop() {
  //CarolOfTheBells();
  playScale();
  // // Carol
  // positions[0] = C_2;
  // steppers.moveTo(positions);
  // steppers.runSpeedToPosition();
  // servoOnePlayNote();

  // delay(10);

  // positions[0] = B_1;
  // steppers.moveTo(positions);
  // steppers.runSpeedToPosition();
  // servoOnePlayNote();

  // positions[0] = C_2;
  // steppers.moveTo(positions);
  // steppers.runSpeedToPosition();
  // servoOnePlayNote();

  // delay(10);

  // positions[0] = A_1;
  // steppers.moveTo(positions);
  // steppers.runSpeedToPosition();
  // servoOnePlayNote();

  // // while (t <= 7) {
  // //   if (t <= 6) {
  // //     positions[0] = t * s_1;
  // //     positions[1] = t * s_2;
  // //   } else {
  // //     positions[0] = t * s_1;
  // //   }
  // //   steppers.moveTo(positions);
  // //   steppers.runSpeedToPosition();

  // //   // Serial.print("Position: ");
  // //   // Serial.println(positions[0]);
  // //   servoTest();

  // //   t++;
  // // }

  // // goToNotes(100, 0);
  // //delay(500);
  // // servoOnePlayNote();
  // // goToNotes(300, 0);
  // // delay(500);
  // // servoOnePlayNote();
  // // goToNotes(0, 100);
  // // delay(500);
  // // servoTwoPlayNote();
  // // goToNotes(0, 100);
  // // delay(500);
  // // servoTwoPlayNote();
  // // servoTest();
  // // delay(1000);
}

void notes(int newNote_1, int newNote_2 /*, int noteLength */) {
  int delta;

  positions[0] = newNote_1;  // round(distance_1 * 123.5 / 64);
  positions[1] = newNote_2;  // round(distance_2 * 123.5 / 64);


  steppers.moveTo(positions);
  steppers.runSpeedToPosition();

  delta = max((abs(newNote_1 - prevNote_1) / s_1), (abs(newNote_2 - prevNote_2) / s_2));

  delay((2 - delta) * 570);

  playNotes();

  prevNote_1 = newNote_1;
  prevNote_2 = newNote_2;
}


void playNotes() {
  servo_pos = 28;
  servo1.write(servo_pos);
  servo2.write(servo_pos);
  delay(80);
  servo_pos = 0;
  servo1.write(servo_pos);
  servo2.write(servo_pos);
  delay(80);
}

void CarolOfTheBells() {
  notes(C_2, C_3);
  notes(B_1, B_2);
  notes(C_2, C_3);
  notes(A_1, A_2);
}

void playScale() {
  int t = 0;

  positions[0] = 0;
  positions[1] = 6 * s_2;

  steppers.moveTo(positions);
  steppers.runSpeedToPosition();

  while (t <= 7) {
    positions[0] = t * s_1;
    steppers.moveTo(positions);
    steppers.runSpeedToPosition();
    servoOnePlayNote();
    t++;
  }
  delay(570);
  t = 6;
  while (t >= 0) {
    positions[1] = t * s_2;
    steppers.moveTo(positions);
    steppers.runSpeedToPosition();
    servoTwoPlayNote();
    t--;
  }
}

void servoOnePlayNote() {
  servo_pos = 28;
  servo1.write(servo_pos);
  delay(80);
  servo_pos = 0;
  servo1.write(servo_pos);
  delay(80);
}

void servoTwoPlayNote() {
  servo_pos = 25;
  servo2.write(servo_pos);
  delay(80);
  servo_pos = 0;
  servo2.write(servo_pos);
  delay(80);
}
