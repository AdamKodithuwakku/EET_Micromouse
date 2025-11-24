#ifndef SYSTEMSTATE_H
#define SYSTEMSTATE_H


// Enum to define different Modes of Operations
enum OperationModes {
  FIRST_RUN,
  SECOND_RUN
};

// Enum to define different states of the robot
enum SystemState {
  SEARCHING,   // Robot is searching for the maze/path
  SOLVING,     // Robot is solving the maze
  COMPLETED,   // Robot has completed the task
  IDLE         // Robot is idle/stopped
};

#endif