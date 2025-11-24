#include "Arduino.h"
#include "MotorDriver.h"

#define PWM_RIGHT 5
#define LOGIC_RIGHT1 11
#define LOGIC_RIGHT2 12

#define PWM_LEFT 6
#define LOGIC_LEFT1 7
#define LOGIC_LEFT2 8

#define MIN_SPEED 80
#define MAX_SPEED 255

#define BASE_SPEED 80

#define BASE_SPEED_LEFT 100
#define BASE_SPEED_RIGHT 110

#define TURN_SPEED_LEFT 100
#define TURN_SPEED_RIGHT 110

#define TURN_LEFT_DELAY 290   // Time to complete a 90-degree left turn (ms)
#define TURN_RIGHT_DELAY 280  // Time to complete a 90-degree right turn (ms)

// Constructor
MotorDriver::MotorDriver() {
  begin();
}

// Initialize pins
void MotorDriver::begin() {
  pinMode(PWM_RIGHT, OUTPUT);
  pinMode(LOGIC_RIGHT1, OUTPUT);
  pinMode(LOGIC_RIGHT2, OUTPUT);

  pinMode(PWM_LEFT, OUTPUT);
  pinMode(LOGIC_LEFT1, OUTPUT);
  pinMode(LOGIC_LEFT2, OUTPUT);
  stop();
}

// Move forward with specified speeds
void MotorDriver::forward(int speedLeft, int speedRight) {
  speedLeft = constrain(speedLeft, MIN_SPEED, MAX_SPEED);
  speedRight = constrain(speedRight, MIN_SPEED, MAX_SPEED);

  // Right motor forward
  digitalWrite(LOGIC_RIGHT1, HIGH);
  digitalWrite(LOGIC_RIGHT2, LOW);
  analogWrite(PWM_RIGHT, speedRight);

  // Left motor forward
  digitalWrite(LOGIC_LEFT1, HIGH);
  digitalWrite(LOGIC_LEFT2, LOW);
  analogWrite(PWM_LEFT, speedLeft);
}

void MotorDriver::forwardPID(int pid) {

  int speedLeft = constrain(BASE_SPEED_LEFT - pid, MIN_SPEED, MAX_SPEED);
  int speedRight = constrain(BASE_SPEED_RIGHT + pid, MIN_SPEED, MAX_SPEED);

  // Right motor forward
  digitalWrite(LOGIC_RIGHT1, HIGH);
  digitalWrite(LOGIC_RIGHT2, LOW);
  analogWrite(PWM_RIGHT, speedRight);

  // Left motor forward
  digitalWrite(LOGIC_LEFT1, HIGH);
  digitalWrite(LOGIC_LEFT2, LOW);
  analogWrite(PWM_LEFT, speedLeft);
}

// Move backward with specified speeds
void MotorDriver::backward(int speedLeft, int speedRight) {
  speedLeft = constrainSpeed(speedLeft);
  speedRight = constrainSpeed(speedRight);

  // Right motor backward
  digitalWrite(LOGIC_RIGHT1, LOW);
  digitalWrite(LOGIC_RIGHT2, HIGH);
  analogWrite(PWM_RIGHT, speedRight);

  // Left motor backward
  digitalWrite(LOGIC_LEFT1, LOW);
  digitalWrite(LOGIC_LEFT2, HIGH);
  analogWrite(PWM_LEFT, speedLeft);
}


// Turn right (rotate in place); this is using the Delay method.
void MotorDriver::turnRight() {
  //Stopping the robot before turing
  stop();
  delay(20);


  // Right motor backward
  digitalWrite(LOGIC_RIGHT1, LOW);
  digitalWrite(LOGIC_RIGHT2, HIGH);

  // Left motor forward
  digitalWrite(LOGIC_LEFT1, HIGH);
  digitalWrite(LOGIC_LEFT2, LOW);

  analogWrite(PWM_LEFT, TURN_SPEED_LEFT - 30);
  analogWrite(PWM_RIGHT, TURN_SPEED_RIGHT - 30);
  delay(20);
  analogWrite(PWM_LEFT, TURN_SPEED_LEFT - 15);
  analogWrite(PWM_RIGHT, TURN_SPEED_RIGHT - 15);
  delay(10);

  analogWrite(PWM_RIGHT, TURN_SPEED_RIGHT);
  analogWrite(PWM_LEFT, TURN_SPEED_LEFT);

  //Match the delay such that robot makes a crisp 90 degree turn
  delay(TURN_RIGHT_DELAY);
}

// Turn left (rotate in place), this is using the delay method.
void MotorDriver::turnLeft() {
  //Stopping the robot before turing
  stop();
  delay(20);

  // Right motor forward
  digitalWrite(LOGIC_RIGHT1, HIGH);
  digitalWrite(LOGIC_RIGHT2, LOW);

  // Left motor backward
  digitalWrite(LOGIC_LEFT1, LOW);
  digitalWrite(LOGIC_LEFT2, HIGH);


  analogWrite(PWM_LEFT, TURN_SPEED_LEFT - 30);
  analogWrite(PWM_RIGHT, TURN_SPEED_RIGHT - 30);
  delay(20);
  analogWrite(PWM_LEFT, TURN_SPEED_LEFT - 15);
  analogWrite(PWM_RIGHT, TURN_SPEED_RIGHT - 15);
  delay(10);


  analogWrite(PWM_RIGHT, TURN_SPEED_RIGHT);
  analogWrite(PWM_LEFT, TURN_SPEED_LEFT);
  //Match the delay such that robot makes a crisp 90 degree turn
  delay(TURN_LEFT_DELAY);
}

// Stop all motors
void MotorDriver::stop() {
  digitalWrite(LOGIC_RIGHT1, LOW);
  digitalWrite(LOGIC_RIGHT2, LOW);
  analogWrite(PWM_RIGHT, 0);

  digitalWrite(LOGIC_LEFT1, LOW);
  digitalWrite(LOGIC_LEFT2, LOW);
  analogWrite(PWM_LEFT, 0);
}

// Set individual motor - left
void MotorDriver::setMotorLeft(int speed, bool forward) {
  speed = constrainSpeed(abs(speed));

  if (forward) {
    digitalWrite(LOGIC_LEFT1, HIGH);
    digitalWrite(LOGIC_LEFT2, LOW);
  } else {
    digitalWrite(LOGIC_LEFT1, LOW);
    digitalWrite(LOGIC_LEFT2, HIGH);
  }
  analogWrite(PWM_LEFT, speed);
}

// Set individual motor - right
void MotorDriver::setMotorRight(int speed, bool forward) {
  speed = constrainSpeed(abs(speed));

  if (forward) {
    digitalWrite(LOGIC_RIGHT1, HIGH);
    digitalWrite(LOGIC_RIGHT2, LOW);
  } else {
    digitalWrite(LOGIC_RIGHT1, LOW);
    digitalWrite(LOGIC_RIGHT2, HIGH);
  }
  analogWrite(PWM_RIGHT, speed);
}