#include <math.h>
#include "UltrasonicSensor.h"
#include "MotorDriver.h"
#include "Communicator.h"

#define TRIGGER_LEFT A4
#define ECHO_LEFT A5
#define TRIGGER_FRONT 2
#define ECHO_FRONT 3
#define TRIGGER_RIGHT A1
#define ECHO_RIGHT A0

#define OBSTACLE_THRESHOLD 12.0  // Front obstacle threshold
#define WALL_THRESHOLD 15.0      // Maximum distance from wall to activate wall follower
#define FORWARD_DELAY 300        // Short forward movement after turn
#define STOP_AFTER_TURN 500      // Stop for 1 second after turn

// PD constants for wall following
#define KP_STRAIGHT 0.25
#define KD_STRAIGHT 0.10

// Reference points for walls
#define SETPOINT_LEFT 8.30   // cm - desired distance from left wall
#define SETPOINT_RIGHT 8.20  // cm - desired distance from Right wall


// Create objects for ultrasonic sensors
UltrasonicSensor ultrasonicLeft(TRIGGER_LEFT, ECHO_LEFT);
UltrasonicSensor ultrasonicFront(TRIGGER_FRONT, ECHO_FRONT);
UltrasonicSensor ultrasonicRight(TRIGGER_RIGHT, ECHO_RIGHT);

// Create object for motor driver
MotorDriver robot;

//Object for the Communication module
Communicator communicator;

// PD variables
float error = 0.0;
float derivative = 0.0;
float lastError = 0.0;
float lastLeftError = 0.0;
float lastRightError = 0.0;
int pidValue = 0;

// Sensor readings
float distLeft = 0.0;
float distFront = 0.0;
float distRight = 0.0;

void setup() {
  Serial.begin(9600);
  Serial.println("Wall Following Robot Initialized");
  robot.stop();
  delay(2000);
}
void loop(){
  // followLeftWall();
  // delay(100);
  motor.forward();
}
void loopNot() {
  // Read all sensors
  distFront = ultrasonicFront.distance();
  distRight = ultrasonicRight.distance();
  distLeft = ultrasonicLeft.distance();

  // Print sensor data for debugging
  // Serial.print("L: ");
  // Serial.print(distLeft);
  // Serial.print(" | F: ");
  // Serial.print(distFront);
  // Serial.print(" | R: ");
  // Serial.println(distRight);

  // Simple wall following logic
  if (distFront <= OBSTACLE_THRESHOLD) {
    // Obstacle ahead - turn right
    if (distLeft <= distRight) {
      if (distLeft <= WALL_THRESHOLD && distRight <= WALL_THRESHOLD) {
        // Serial.println("Deadend ahead - Turning Around");

        robot.turnRight();
        robot.turnRight();
      } else {
        // Serial.println("Obstacle ahead - Turning Right");
        robot.turnRight();
      }
    }
    else {
      // Obstacle ahead turn left
      if (distLeft <= WALL_THRESHOLD && distRight <= WALL_THRESHOLD) {
        // Serial.println("Deadend ahead - Turning Around");
        robot.turnLeft();
        robot.turnLeft();
      } else {
        // Serial.println("Obstacle ahead - Turning Left");
        robot.turnLeft();
      }
    }


    robot.stop();
    delay(STOP_AFTER_TURN);

    resetPID();

  } else if (distLeft <= WALL_THRESHOLD) {
    // Follow the left wall using PD control

    //TODO: Scan For Walls on the sides.
    //..if()

    followLeftWall();
    delay(100);

  } else {

    //NO Wall on the front
    // Serial.println("No left wall");

    if (distRight <= WALL_THRESHOLD) {
      //Following Right wall
      //TODO: Scan for Walls on the sides.
      followRightWall();
      delay(100);
    } else {
      // NO REFEREANCE
      // Path Is Open
      // No Front Wall, Left, Right
      while (!ultrasonicFront.isFoundObject(OBSTACLE_THRESHOLD) && !ultrasonicLeft.isFoundObject(WALL_THRESHOLD) && !ultrasonicRight.isFoundObject(WALL_THRESHOLD)) {
        robot.forwardPID(0);
        delay(100);
        robot.stop();
      }
      
      noTone(13);
      //In a --Junction
    }
  }


  robot.stop();
  delay(30);
}

void followLeftWall() {
  // Following the Left Wall with PD control
  error = distLeft - SETPOINT_LEFT;
  derivative = (error - lastLeftError);

  float correction = error * KP_STRAIGHT + derivative * KD_STRAIGHT;

  correction = constrain(correction, -2, 2);

  pidValue = (int)correction;

  robot.forwardPID(pidValue);
  lastError = error;
}



void followRightWall() {
  // Following the Right Wall with PD control
  error = SETPOINT_RIGHT - distRight;
  derivative = (lastRightError - error);

  float correction = error * KP_STRAIGHT + derivative * KD_STRAIGHT;
  correction = constrain(correction, -2, 2);

  pidValue = (int)correction;

  robot.forwardPID(pidValue);
  lastError = error;
}

void resetPID() {
  lastLeftError = 0;
  lastRightError = 0;
  lastError = 0;
  derivative = 0;
  error = 0;
}