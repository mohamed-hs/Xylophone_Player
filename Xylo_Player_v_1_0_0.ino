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

#include <Stepper.h>
#include <Servo.h>

#define STEPS 64  // number of strides to reach 360 rotation

Stepper stepper1(STEPS, STEP1_1, STEP1_2, STEP1_3, STEP1_4);
Stepper stepper2(STEPS, STEP1_1, STEP1_2, STEP1_3, STEP1_4);

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

  stepper1.setSpeed(60);
}

void loop() {

  stepperTest();
  servoTest();
}

void stepperTest() {
  stepper1.step(10);
  delay(1000);
  stepper2.step(10);
  delay(1000);
}

void servoTest() {
  for (pos = 0; pos <= 180; pos += 1) {
    // in steps of 1 degree
    servo1.write(pos);
    servo2.write(pos);
    delay(15);
  }
  for (pos = 180; pos >= 0; pos -= 1) {
    servo1.write(pos);
    servo2.write(pos);
    delay(15);
  }
}