#ifndef MOTORDRIVER_H
#define MOTORDRIVER_H



#include <Arduino.h>

class MotorDriver {
  private:
    // Helper function to constrain speed
    int constrainSpeed(int speed);
    
  public:
    // Constructor
    MotorDriver();
    
    // Initialize pins
    void begin();
    
    // Move forward with specified speeds (0-255)
    void forward(int speedLeft, int speedRight);
    void forwardPID(int pidValue);

    // Move backward with specified speeds
    void backward(int speedLeft, int speedRight);
    
    // Turn right (rotate in place)
    void turnRight();
    
    // Turn left (rotate in place)
    void turnLeft();
    
    // Stop all motors
    void stop();
    
    // Set individual motor
    void setMotorLeft(int speed, bool forward);
    void setMotorRight(int speed, bool forward);
};

#endif