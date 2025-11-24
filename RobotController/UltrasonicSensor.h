#ifndef ULTRASONICSENSOR_H

#define ULTRASONICSENSOR_H

#include <Arduino.h>

class UltrasonicSensor {
  private:
    int triggerPin;
    int echoPin;
    long duration;
    float distanceCm;
    
  public:
    // Constructor
    UltrasonicSensor(int trig, int echo);
    
    // Initialize pins
    void begin();
    
    // Measure distance in centimeters
    float distance();
    
    // Check if object is found within specified distance
    bool isFoundObject(float threshold);
    
    // Get raw pulse duration
    long getDuration();
};

#endif